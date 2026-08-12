# Design Note — Vehicle Rental System (Lab 14)

**Course:** Object-Oriented Programming with C++
**Lab:** 14 — Design a Vehicle Rental System

This note was written before the C++ code was implemented, and updated afterwards so that it
matches the final code exactly. It explains **why** the design looks the way it does, not just
what it does.

---

## 1. Vehicle Type Design — Inheritance vs. a Type Field

### The decision

`Car`, `Motorbike` and `Truck` **inherit from an abstract base class `Vehicle`**.

```
        Vehicle  (abstract)
        /   |   \
     Car  Motorbike  Truck
```

### The alternative I considered

The obvious alternative was a single `Vehicle` class with a type field:

```cpp
class Vehicle {
    std::string type;   // "Car", "Motorbike", "Truck"
    int seats;          // only meaningful for a car
    int engineCC;       // only meaningful for a motorbike
    double payload;     // only meaningful for a truck
};
```

I rejected this for three concrete reasons:

1. **Wasted / meaningless data.** Every truck would carry a `seats` field it never uses, and
   every car would carry a `payload` field that means nothing. The object would always be
   partly invalid.
2. **The pricing rule becomes an `if`-chain.** Cost calculation would turn into
   `if (type == "Truck") ... else if (type == "Motorbike") ...`. Every time a new vehicle type
   is added, that chain has to be found and edited — and if the chain is duplicated anywhere,
   one copy will eventually be missed. This is exactly the problem virtual functions solve.
3. **No compiler help.** A typo like `type == "truck"` compiles fine and silently gives the
   wrong price. With separate classes, the type is checked at compile time.

### Why inheritance is genuinely justified here (real *is-a*)

This is not inheritance used only for code reuse. The relationship is a true **is-a**
relationship: *a Car **is a** Vehicle*, *a Truck **is a** Vehicle*. Anywhere the rental system
needs "some vehicle", a `Car`, a `Motorbike` or a `Truck` can be used instead, and the system
does not have to know which one it got. That is the Liskov substitution test, and this design
passes it — `RentalSystem` prices, rents and returns any vehicle purely through the `Vehicle`
interface.

Each subclass also adds a real, type-specific attribute:

| Class     | Extra attribute        | Why it is meaningful          |
|-----------|------------------------|-------------------------------|
| Car       | number of seats        | how many passengers it carries |
| Motorbike | engine capacity (cc)   | the standard way bikes are described |
| Truck     | payload capacity (tonnes) | how much cargo it can legally carry |

### Why `Vehicle` is abstract

`Vehicle` has pure virtual functions, so it cannot be instantiated. That is deliberate: a
"generic vehicle" has **no rental price**, because the price rule (normal / surcharged /
discounted) is defined by the vehicle type. Since a plain `Vehicle` object could not answer
`calculateCost()` sensibly, the language should not allow one to exist. `Vehicle` is a
contract — "everything in the fleet has a name, a daily rate, an availability status, and can
price itself" — not a thing you can park in the garage.

---

## 2. Pricing Design — Where Cost Calculation Lives

### The decision

Pricing lives in the vehicle: **`Vehicle::calculateCost(int days)` is a pure virtual function**,
overridden by `Car`, `Motorbike` and `Truck`.

```cpp
virtual double calculateCost(int days) const = 0;
```

| Class     | Rule implemented                                     |
|-----------|------------------------------------------------------|
| Car       | `dailyRate * days`                                    |
| Truck     | `dailyRate * days * 1.20`  (20% surcharge)            |
| Motorbike | `dailyRate * days * 0.90` **if `days > 7`**, otherwise `dailyRate * days` |

### Why it belongs there and not in `Rental`

The thing that makes the price different is **the type of vehicle**, not the type of rental.
A rental of 10 days is priced one way for a bike and another way for a truck. So the rule
belongs to whichever object knows the difference — the vehicle. If the formula lived in
`Rental`, `Rental` would have to ask "what kind of vehicle is this?" and branch on the answer,
which pushes knowledge of every vehicle type into a class that should not care.

The other alternative — a separate free `calculatePrice(vehicle, days)` function — was rejected
for the same reason: it would need the same type-checking chain, and it would sit outside the
class whose data it uses.

### How polymorphism is involved

`RentalSystem` never knows which concrete class it is holding. It holds a `Vehicle*` and writes
one line:

```cpp
double cost = vehicle->calculateCost(days);
```

At runtime the correct override runs — car, bike or truck. Adding a new vehicle type (say
`Van`) means writing one new class; **no existing code changes**. That is the real problem the
polymorphism solves here.

### Cost is calculated once and stored in the `Rental`

`RentalSystem` computes the cost through the vehicle at the moment the rental is created, then
stores that number inside the `Rental` record. This mirrors real life: the price is agreed
when the vehicle is taken, so a later change to a daily rate must not silently rewrite the
history of past rentals. It also keeps closed rental records readable forever, independently
of the vehicle.

---

## 3. Ownership Design

### The decision

**`RentalSystem` owns everything.** It is the single owner and the single place where state is
changed.

```cpp
std::vector<std::unique_ptr<Vehicle>> fleet;   // owns the vehicles
std::vector<Customer>                 customers; // owns the customers
std::vector<Rental>                   rentals;   // owns every rental record
```

- **Vehicles** are stored as `std::unique_ptr<Vehicle>` because they are polymorphic: the
  element type must be a base pointer so that `Car`, `Motorbike` and `Truck` can live in one
  container. `unique_ptr` gives automatic cleanup (no `delete`, no leaks) and states clearly
  that the fleet owns them. `Vehicle` has a **virtual destructor**, so deleting through the
  base pointer destroys the derived part correctly.
- **Customers and rentals** are plain objects stored **by value**. They are not polymorphic, so
  there is no reason to put them on the heap; `std::vector<Customer>` is simpler and safer.

### Why `Rental` stores IDs, not pointers

A `Rental` stores `customerId` and `vehicleId` — not `Customer*` / `Vehicle*`.

The reason is concrete: `customers` is a `std::vector<Customer>`, and a vector **moves its
elements when it grows**, which would leave any stored pointer dangling as soon as another
customer registered. An integer ID is a stable handle that cannot dangle. Using IDs for both
sides also keeps the design consistent and matches how the public API is used
(`rentVehicle(customerId, vehicleId, days)`).

### How active rentals are tracked

Two status flags, both maintained **only** by `RentalSystem`:

- `Vehicle::available` — false while the vehicle is out.
- `Customer::activeRental` — true while that customer has an open rental.

These are cached status flags: the same fact could be recomputed by scanning the rentals list,
but storing it makes the checks in `rentVehicle()` direct and easy to read. The risk with any
cached state is that the copies disagree, so the design contains that risk deliberately: no
other class can set them (the setters exist, but only `RentalSystem` calls them), and they are
updated together in exactly two functions — `rentVehicle()` sets both, `returnVehicle()` clears
both. There is no second path that can change one without the other.

---

## 4. Class Responsibilities

Seven classes, each with one job. No class exists just to raise the class count.

| Class | Responsibility | Why it exists |
|-------|----------------|---------------|
| `Vehicle` | Abstract base: id, make/model, daily rate, availability, and the *contract* for pricing and describing a vehicle. | Gives the system one type to work with, and one place for everything all vehicles share. |
| `Car` | Number of seats; normal pricing. | A real vehicle type with its own attribute. |
| `Motorbike` | Engine capacity; 10% discount when `days > 7`. | Its pricing behaviour genuinely differs. |
| `Truck` | Payload in tonnes; 20% surcharge. | Its pricing behaviour genuinely differs. |
| `Customer` | Customer id, name, and whether they currently have an active rental. | The rental rule "at most one active rental" is a fact about a customer. |
| `Rental` | One rental record: which customer, which vehicle, how many days, the agreed cost, and whether it is still active. | R5 requires returned rentals to survive as **closed records**, so a rental must be an object with its own lifetime — it cannot just be a flag on the vehicle. |
| `RentalSystem` | Owns fleet/customers/rentals; validates and processes rentals and returns; prints summaries. | The use cases (rent, return, report) touch several objects at once, so they belong to a coordinator. |

### Why this is not a God class

`RentalSystem` coordinates, but it does not do the other classes' work:

- it does **not** calculate prices — it asks the vehicle;
- it does **not** know what makes a truck different from a bike;
- it does **not** reach into anyone's data — every member of every class is `private` and is
  reached through small public functions.

Its own job — validating a request and keeping fleet, customer and rental records consistent —
is genuinely one responsibility.

---

## 5. Runtime Polymorphism — Exact Location

**Primary location:** `RentalSystem::rentVehicle()` in `src/RentalSystem.cpp`.

```cpp
Vehicle* vehicle = findVehicle(vehicleId);   // static type: Vehicle*
...
double cost = vehicle->calculateCost(days);  // <-- runtime polymorphism
```

- **Which virtual function is called:** `Vehicle::calculateCost(int days) const`, declared pure
  virtual in `Vehicle` and overridden in `Car`, `Motorbike` and `Truck`.
- **Why it is virtual:** the correct formula is only known from the *actual* object type, and
  that type is only known at runtime — the vehicle came out of a mixed fleet container. Without
  `virtual`, the call would resolve to the base version at compile time and every vehicle would
  be priced identically.
- **Why the base interface is useful:** `fleet` is a `std::vector<std::unique_ptr<Vehicle>>`
  holding cars, bikes and trucks together. Searching, renting, returning and reporting are all
  written **once** against `Vehicle`, instead of once per type. A new vehicle type is one new
  class and zero edits to `RentalSystem`.
- **What differs between the three:** Car returns `rate * days`; Truck returns
  `rate * days * 1.20`; Motorbike returns `rate * days * 0.90` when the rental is longer than
  7 days, and `rate * days` otherwise.

**Two more virtual functions, used for reporting** (also called through `Vehicle*`, in
`RentalSystem`'s printing functions):

- `typeName()` → `"Car"` / `"Motorbike"` / `"Truck"` — labels the vehicle in the summary.
- `specification()` → `"5 seats"` / `"125 cc engine"` / `"8 tonne payload"` — each subclass
  reports its own extra attribute. The base class cannot produce this string, because the base
  class does not have the data; this is the natural place for the subclass to speak for itself.

These are not decoration: without them the summary would need a type-checking chain in the
printing code, which is the exact thing the class hierarchy exists to avoid.

---

## 6. Deliberately Excluded Features

The following were consciously left out. They are outside the scope of Lab 14 and would add
size without adding OOP value:

- **File persistence / database** — the assignment is about class design; data lives in memory
  for one run of the program.
- **GUI, networking, multithreading** — not required, and they would bury the OOP design.
- **Login / authentication and payment processing** — no requirement mentions them.
- **Reservation or booking dates** — rentals are measured in *number of days*, exactly as the
  specification states; real calendar dates are not required.
- **Multiple simultaneous rentals per customer** — explicitly forbidden by R2, so the design
  enforces one active rental instead of supporting many.
- **Late fees, damage charges, insurance, taxes** — not in the pricing rules given.
- **Templates and design patterns (Factory, Strategy, etc.)** — a Strategy object for pricing
  was considered and rejected: virtual functions already give exactly the same flexibility here,
  with far less machinery for a system this size.
- **Exceptions** — invalid operations are rejected with a clear message and a `false` return
  value. For a small console program that keeps the control flow visible and easy to explain;
  exceptions would be a heavier tool than the problem needs.
