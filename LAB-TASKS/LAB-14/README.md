# Vehicle Rental System

**Course:** Object-Oriented Programming with C++
**Lab:** 14 — Design a Vehicle Rental System

---

## Project Description

A small console program that models a vehicle rental company. The company keeps a fleet of
cars, motorbikes and trucks, registers customers, rents vehicles out for a number of days,
takes them back, and prints a summary of what is currently rented and what is still available.

Each vehicle type prices its own rentals: a truck adds a 20% surcharge, a motorbike gives a
10% discount on rentals longer than 7 days, and a car is charged at the plain daily rate. The
rental system never checks what kind of vehicle it is holding — it just asks the vehicle for
the cost, and the correct rule runs. That is where the runtime polymorphism in this lab lives.

---

## Design Questions — Answered

These are the five design questions the assignment asks. Short answers here; the full reasoning
and the rejected alternatives are in [DESIGN_NOTE.md](DESIGN_NOTE.md).

### Q1. How are the three vehicle types modelled — subclasses, or a type field?

**Subclasses.** `Car`, `Motorbike` and `Truck` each inherit from an abstract `Vehicle`.

I chose this because the relationship is a genuine *is-a* (a Truck **is a** Vehicle), and
because the three types differ in **behaviour**, not just in labelling: each one prices a rental
by a different rule. A type field cannot carry behaviour — it can only be tested — so the
pricing rule would have to become an `if (type == "Truck") … else if (type == "Motorbike") …`
chain somewhere outside the class. Each type also has an attribute the others do not
(seats / engine cc / payload tonnes), and with a single class every object would carry all three
fields with two of them meaningless.

**When the type-field approach would be better:** if the "types" differed only by *data* and
never by *behaviour* — for example if every vehicle were priced identically and `type` were just
a word printed in a report, or a filter in a search. Then three classes would be ceremony around
a string, and one class with a `type` field would be simpler and easier to read. The field also
wins when types must be created from external input at run time (a config file listing 40 vehicle
categories), because a class hierarchy would need one class per category, and when a vehicle can
change type after construction — an object cannot change its class, but a field can be reassigned.
Neither applies here: there are exactly three types, fixed at compile time, and they behave
differently.

### Q2. Where does the pricing logic live?

**A virtual method on `Vehicle`:** `virtual double calculateCost(int days) const = 0;`,
overridden in all three subclasses. I own this choice and its consequences.

The thing that changes the price is *the kind of vehicle*, so the rule belongs to the object
that knows what kind it is. The consequence is that adding a `Van` tomorrow means writing one
new class — `RentalSystem` does not change at all.

The two placements I rejected, and what they would have cost:

- **A method on `Rental`** — `Rental` would have to ask "what kind of vehicle is this?" and
  branch, which drags knowledge of every vehicle type into a class that should only be a record.
  Every new vehicle type would then require editing `Rental`.
- **A free function `calculatePrice(vehicle, days)`** — same branching problem, and it sits
  outside the class whose data it uses, so it cannot be part of the `Vehicle` contract; nothing
  forces a new vehicle type to be handled at all, and a missed case fails silently at run time
  instead of at compile time.

One consequence I accepted: the *result* is stored in the `Rental`, not recalculated on demand.
`RentalSystem` calls `calculateCost()` once when the rental is created and saves the number, so
changing a daily rate later cannot rewrite the price of a rental that already happened.

### Q3. Who owns the rental record?

**A central `RentalSystem` owns all of them**, in `std::vector<Rental> rentals`. It also owns
the fleet and the customers, and it is the only class that changes their state.

- **`Customer` does not hold rentals.** It holds one `bool` — whether it currently has an active
  rental — because that is the rule the assignment states (at most one at a time). It does not
  own the record.
- **`Vehicle` does know whether it is rented**, via a private `available` flag, because
  availability is a property of the vehicle and R1 asks for it to be stored. But the vehicle does
  not own or point at the rental either.
- **`Rental` refers to both by id**, not by pointer — a `std::vector<Customer>` moves its
  elements when it grows, so a stored `Customer*` would dangle as soon as another customer
  registered. An `int` id is a stable handle.

So the record has exactly one owner and one storage location. The two status flags are cached
facts *about* that record; both are private, both are changed only by `RentalSystem`, and both
are updated together in exactly two functions — `rentVehicle()` sets them, `returnVehicle()`
clears them. There is no third path that could set one without the other, which is what keeps
them from drifting apart.

### Q4. How many classes, and does a `Fleet` class add value?

**Seven:** `Vehicle`, `Car`, `Motorbike`, `Truck`, `Customer`, `Rental`, `RentalSystem`.

- **`Rental` earns its place.** R5 requires a returned rental to survive as a *closed record*.
  If a rental were just fields on the vehicle, that information would be overwritten the moment
  the vehicle was rented again and the history would be gone. A record that outlives the event
  it describes needs its own lifetime — so it needs its own class.
- **A `Fleet` class was considered and rejected.** It would be a thin wrapper around
  `std::vector<std::unique_ptr<Vehicle>>` plus an `addVehicle` and a `find`, and `RentalSystem`
  would end up forwarding calls to it — more indirection to read through, no new behaviour.
  A `Fleet` would start paying for itself once fleet logic grew beyond storage: multiple depots,
  transferring vehicles between branches, servicing schedules, or "find me the cheapest available
  truck" queries. At that point `RentalSystem` would be doing two jobs and `Fleet` would be the
  natural place to split. With four vehicles and one branch, it obscures more than it clarifies.
- **A `PricingStrategy` class was also rejected** — virtual functions already give exactly the
  same flexibility here with far less machinery.

The test I applied to every class: *does removing it force duplicated logic or a broken
requirement?* If not, it does not exist.

### Q5. Where does runtime polymorphism actually appear?

**The dispatch is at [`src/RentalSystem.cpp:141`](src/RentalSystem.cpp#L141):**

```cpp
Vehicle* vehicle = findVehicle(vehicleId);    // static type: Vehicle*
...
double cost = vehicle->calculateCost(days);   // <-- the Car/Motorbike/Truck override runs
```

**The `main()` lines that drive it** are [`main.cpp:51`](main.cpp#L51),
[`main.cpp:54`](main.cpp#L54) and [`main.cpp:57`](main.cpp#L57):

```cpp
system.rentVehicle(1, 101, 3);    // Car       -> 45 x 3          = $135.00
system.rentVehicle(2, 201, 10);   // Motorbike -> 12 x 10 x 0.90  = $108.00
system.rentVehicle(3, 301, 4);    // Truck     -> 150 x 4 x 1.20  = $720.00
```

Three identical calls into the same function produce three different pricing rules. Nothing in
`main()` and nothing in `RentalSystem` names a vehicle type — the objects supply the behaviour
themselves.

**Why the call sits there and not directly in `main()`:** the polymorphism has to live where the
code genuinely does not know the concrete type, and that place is `RentalSystem`. It holds a
mixed `std::vector<std::unique_ptr<Vehicle>>`, and it looks vehicles up **by id**, so what comes
back is a `Vehicle*` — the concrete type is not merely hidden, it is genuinely unknown at that
point. `main()` is only the demo driver: it happens to know it wrote `make_unique<Truck>` on
[`main.cpp:33`](main.cpp#L33), so a virtual call written there would be a demonstration of the
syntax rather than a use of it. Putting a `Vehicle*` loop in `main()` purely to show a base
pointer would prove less, not more — and it would mean `main()`, not the system, was doing the
work.

The same dispatch drives the reporting, where each vehicle labels and describes itself in the
summary tables: `typeName()` through a `const Vehicle*` at
[`RentalSystem.cpp:231`](src/RentalSystem.cpp#L231), and `typeName()` / `specification()` through
a `const Vehicle&` bound to each fleet element at
[`RentalSystem.cpp:306-307`](src/RentalSystem.cpp#L306-L307) — virtual dispatch works through a
base **reference** exactly as it does through a base pointer. Without these the printing code
would need the same type-checking chain the hierarchy exists to remove.

---

## Requirements Implemented

| # | Requirement | Where it is handled |
|---|-------------|---------------------|
| R1 | Fleet of multiple vehicles (make/model, daily rate, availability) | `Vehicle`, `RentalSystem::addVehicle` |
| R1 | Three vehicle types: Car, Motorbike, Truck | `Car`, `Motorbike`, `Truck` |
| R2 | Customer registration with a unique id | `Customer`, `RentalSystem::registerCustomer` |
| R2 | At most one active rental per customer | `Customer::hasActiveRental`, checked in `rentVehicle` |
| R3 | Rental processing and validation | `RentalSystem::rentVehicle` |
| R4 | Cost = daily rate × days | `Car::calculateCost` |
| R4 | Truck 20% surcharge | `Truck::calculateCost` |
| R4 | Motorbike 10% discount when days > 7 | `Motorbike::calculateCost` |
| R5 | Vehicle return, record kept as **closed** | `RentalSystem::returnVehicle`, `Rental::close` |
| R6 | Active rentals summary (customer, vehicle, days, cost) | `RentalSystem::printActiveRentals` |
| R6 | Fleet availability (available vs rented counts) | `RentalSystem::printFleetAvailability` |
| — | Rental history, so closed records are visible | `RentalSystem::printRentalHistory` |

---

## OOP Concepts Demonstrated

- **Classes and objects** — seven classes, each with one clear job (see `DESIGN_NOTE.md`).
- **Encapsulation** — every data member in every class is `private`. Nothing is reached
  directly; state changes go through small, named functions such as `markAsRented()`,
  `startRental()` and `close()`.
- **Inheritance** — `Car`, `Motorbike` and `Truck` inherit from `Vehicle` on a genuine
  *is-a* relationship, and each adds its own attribute (seats / engine cc / payload).
- **Abstraction** — `Vehicle` is an abstract class: it defines *what* every vehicle must be
  able to do (price itself, name its type, describe itself) without saying *how*.
- **Runtime polymorphism** — the fleet is a `std::vector<std::unique_ptr<Vehicle>>`, and
  `calculateCost()`, `typeName()` and `specification()` are called through the base pointer,
  so the right override runs for each object.
- **Composition / association** — `RentalSystem` **owns** the vehicles, customers and rental
  records (composition: they die with the system). A `Rental` only **refers to** its customer
  and vehicle, by id (association: it does not own them).
- **Constructors and destructors** — every class initialises its members in a constructor
  initialiser list; `Vehicle` has a **virtual destructor** because vehicles are deleted
  through a base pointer.
- **`const` correctness** — read-only functions (`getDailyRate()`, `calculateCost()`, all the
  print functions) are `const`, strings are passed by `const&` to avoid copying, and the
  lookup helpers have both a `const` and a non-`const` version.

---

## Project Structure

```
LAB-14/
├── README.md                 this file
├── DESIGN_NOTE.md            the design decisions and why they were made
├── IMPLEMENTATION_PLAN.md    how the work was carried out, phase by phase
├── VIVA_NOTES.md             likely viva questions with short answers
│
├── include/                  class declarations (interface)
│   ├── Vehicle.h             abstract base class
│   ├── Car.h
│   ├── Motorbike.h
│   ├── Truck.h
│   ├── Customer.h
│   ├── Rental.h              one rental record
│   └── RentalSystem.h        owns the fleet, customers and rentals
│
├── src/                      member function definitions (implementation)
│   ├── Vehicle.cpp
│   ├── Car.cpp
│   ├── Motorbike.cpp
│   ├── Truck.cpp
│   ├── Customer.cpp
│   ├── Rental.cpp
│   └── RentalSystem.cpp
│
└── main.cpp                  the demonstration scenario
```

Headers hold the declarations and the comments explaining each class; the `.cpp` files hold
the code. That way a reader can understand the design from `include/` alone.

---

## How to Compile

From inside the `LAB-14` folder:

```bash
g++ -std=c++17 -Wall -Wextra -I include main.cpp src/Vehicle.cpp src/Car.cpp src/Motorbike.cpp src/Truck.cpp src/Customer.cpp src/Rental.cpp src/RentalSystem.cpp -o rental
```

This exact command was used to build the project, and it compiles with **no warnings**.
There is no build system (no Makefile or CMake) — the single command above is all that is
needed.

If your shell expands wildcards (Git Bash, Linux, macOS), this shorter form is equivalent:

```bash
g++ -std=c++17 -Wall -Wextra -I include main.cpp src/*.cpp -o rental
```

**Compiler used:** MinGW `g++` 6.3.0 with `-std=c++17`. The code deliberately sticks to core
C++ features (`std::vector`, `std::string`, `std::unique_ptr`, `std::make_unique`, virtual
functions, `override`), so it also builds unchanged on any newer C++17 compiler.

## How to Run

```bash
./rental          # Git Bash / Linux / macOS
rental.exe        # Windows CMD or PowerShell
```

The program takes no input — it runs one fixed scenario and prints the result.

---

## Example Scenario

`main()` runs these steps in order:

1. **Build the fleet** — 4 vehicles: two Cars (Toyota Corolla, Suzuki Alto), a Motorbike
   (Yamaha YBR) and a Truck (Hino 500).
2. **Register customers** — 4 customers. The fourth stays free so it can be used in the
   validation checks.
3. **Process 3 rentals**, one per vehicle type, so all three pricing rules are visible:
   - Car, 3 days → `45.00 × 3` = **$135.00**
   - Motorbike, 10 days → `12.00 × 10 × 0.90` = **$108.00** (longer than 7 days)
   - Truck, 4 days → `150.00 × 4 × 1.20` = **$720.00** (20% surcharge)
4. **Try six invalid operations**, all of which are refused with a clear message: renting an
   already-rented vehicle, a second rental for a customer who already has one, a 0-day rental,
   a negative-day rental, an unregistered customer, and a vehicle that is not in the fleet
   (plus a duplicate customer id).
5. **Return a vehicle** — the Corolla comes back. Returning it a second time is refused
   cleanly. Then the same customer rents again, which proves the return really did clear
   their active-rental status (the identical request was refused in step 4).
6. **Print the summary** — active rentals, the full rental history (rental #1 shows as
   **CLOSED** but is still on record, as R5 requires), and the fleet availability counts.

---

## Design Documentation

- **[DESIGN_NOTE.md](DESIGN_NOTE.md)** — the required design note: why inheritance was chosen
  over a type field, where pricing lives and why, who owns the rental records, what each class
  is responsible for, the exact location of the runtime polymorphism, and what was left out.
- **[IMPLEMENTATION_PLAN.md](IMPLEMENTATION_PLAN.md)** — the phases the work went through,
  with checklists and the actual test results.
- **[VIVA_NOTES.md](VIVA_NOTES.md)** — short answers to the questions most likely to be asked
  about this design.

---

## Scope

Intentionally **not** implemented, because the assignment does not ask for them and they would
hide the OOP design behind extra machinery: file saving or a database, a GUI, networking,
login/authentication, payment processing, calendar booking dates, late fees or taxes, multiple
simultaneous rentals per customer (explicitly forbidden by R2), templates, and design patterns.
`DESIGN_NOTE.md` section 6 explains each exclusion.
