# Viva Notes — Vehicle Rental System (Lab 14)

Short answers to the questions most likely to come up. Every answer matches the code in this
folder.

---

### 1. Why did you use inheritance here?

Because there is a real **is-a** relationship: a Car *is a* Vehicle, a Truck *is a* Vehicle.
The rental system works with "some vehicle" and does not need to know which kind it got, so any
subclass can stand in for the base — that is the test for correct inheritance, and this design
passes it. I did not use inheritance just to share code; each subclass also adds its own data
(seats, engine cc, payload) and its own pricing rule.

### 2. Why is `Vehicle` an abstract base class?

Because a generic vehicle has no rental price. The price depends on the type — plain,
surcharged, or discounted — so a plain `Vehicle` object could not answer `calculateCost()`
sensibly. Making the function pure virtual means the compiler refuses to create a `Vehicle`,
which is exactly what I want. `Vehicle` is a contract, not an object you can park in a garage.

### 3. Why is `calculateCost()` virtual?

Because the correct formula is only known from the actual object type, and that type is only
known at run time — the vehicle comes out of a mixed fleet container as a `Vehicle*`. If the
function were not virtual, the call would bind at compile time to the base version and every
vehicle would be priced the same, so the truck surcharge and the bike discount would silently
disappear.

### 4. Where exactly does runtime polymorphism happen?

In `RentalSystem::rentVehicle()` (`src/RentalSystem.cpp`):

```cpp
Vehicle* vehicle = findVehicle(vehicleId);    // static type is Vehicle*
double cost = vehicle->calculateCost(days);   // the Car/Motorbike/Truck override runs
```

It also happens in the printing functions, where `typeName()` and `specification()` are called
through the same base pointers to build the summary tables. All three functions are pure
virtual in `Vehicle` and overridden in all three subclasses.

### 5. Why is `Rental` a separate class?

Because requirement R5 says a returned rental must survive as a **closed record**. If a rental
were just a flag or a couple of fields on the vehicle, the information would be overwritten the
moment the vehicle was rented again, and the history would be gone. A rental has its own
lifetime and its own data — customer, vehicle, days, agreed cost, active/closed — so it is its
own object. Returning a vehicle calls `Rental::close()`, which flips a flag; nothing is erased.

### 6. Who owns the rental records?

`RentalSystem` does. It holds `std::vector<Rental> rentals`, and it is also the only owner of
the fleet and the customers. Single ownership was a deliberate choice: if both the customer and
the vehicle held a copy of the rental, the two copies could disagree about whether it was still
active. Here there is one record and one owner.

### 7. Why is a customer limited to one active rental?

That is the business rule in requirement R2. It is enforced in `rentVehicle()`, which checks
`customer->hasActiveRental()` before creating anything and rejects the request with a message
if it is true. The flag is set in `rentVehicle()` and cleared in `returnVehicle()` — those are
the only two places that touch it.

### 8. How do you prevent renting an unavailable vehicle?

Every `Vehicle` carries a private `available` flag. `rentVehicle()` checks
`vehicle->isAvailable()` and refuses if the vehicle is out. On a successful rental it calls
`markAsRented()`, and `returnVehicle()` calls `markAsReturned()`. The demo proves this: a free
customer trying to take a car that is already out is rejected.

### 9. How does the truck surcharge work?

`Truck::calculateCost()` computes the normal cost and multiplies by 1.20:

```cpp
double baseCost = getDailyRate() * days;
return baseCost * 1.20;      // 20% surcharge
```

In the demo: 150.00 × 4 = 600.00, plus 20% = **720.00**.

### 10. How does the motorbike discount work?

`Motorbike::calculateCost()` applies 10% off only when the rental is **longer than** 7 days:

```cpp
double baseCost = getDailyRate() * days;
if (days > 7) return baseCost * 0.90;
return baseCost;
```

In the demo: 12.00 × 10 = 120.00, less 10% = **108.00**. At exactly 7 days there is no
discount (7 × 12.00 = 84.00) — I tested that boundary specifically.

### 11. Why did you use `std::vector`?

The fleet, the customer list and the rental list all grow at run time, and I do not know their
size in advance. `std::vector` grows on its own, knows its own size, and frees its memory
automatically — a raw array would need a fixed size and manual memory handling for no benefit.

### 12. Why did you use `unique_ptr` for vehicles but not for customers and rentals?

`unique_ptr` is needed for the vehicles because the fleet is **polymorphic**: cars, bikes and
trucks must live in one container, which means the element type has to be a base-class pointer.
`unique_ptr<Vehicle>` states that the fleet owns those objects and frees them automatically, so
there is no `delete` anywhere in the project. Customers and rentals are not polymorphic — there
is only one kind of each — so putting them on the heap would add pointers and risk for nothing.
They are stored by value in `std::vector<Customer>` and `std::vector<Rental>`.

Related: because `Vehicle` objects are destroyed through a `Vehicle*`, `Vehicle` has a
**virtual destructor**. Without it, deleting a `Truck` through a `Vehicle*` would be undefined
behaviour and the derived part would not be cleaned up.

### 13. Why is `Rental` storing ids instead of pointers to `Customer` and `Vehicle`?

Because `customers` is a `std::vector<Customer>`, and a vector **moves its elements when it
grows**. Any `Customer*` stored earlier would dangle as soon as the next customer registered.
An `int` id is a stable handle that can never dangle, and the system looks the objects up when
it needs them.

### 14. Why is all the data private?

So that an object cannot be put into an invalid state from outside. For example, nothing can
set a vehicle to "available" while a rental for it is still open, because `available` is
private and only `RentalSystem` calls `markAsRented()` / `markAsReturned()`, always in pairs
with the customer's flag. Public data would let any part of the program change one half of that
pair and break the invariant.

### 15. Isn't `RentalSystem` a God class?

No. It coordinates, but it does not do the other classes' work: it never calculates a price
(it asks the vehicle), it never checks what type a vehicle is, and it never reaches into
another object's data. Its single responsibility is keeping the fleet, the customers and the
rental records consistent with each other — which is genuinely one job, and it is the job the
use cases "rent" and "return" require, since each one touches three objects at once.

### 16. Why keep status flags on the vehicle and the customer, when both could be worked out from the rentals list?

They are cached status flags, kept for direct and readable checks. I know the risk with cached
state is that the copies disagree, so the design contains it: both flags are private, only
`RentalSystem` changes them, and they are updated together in exactly two functions —
`rentVehicle()` sets both, `returnVehicle()` clears both. There is no third path that could set
one without the other.

### 17. What would you change if the system became much larger?

- Replace the linear `find...` searches with a hash map from id to object (`std::unordered_map`)
  — with thousands of vehicles, scanning a vector for every lookup becomes slow.
- Return a result/status type instead of `bool` + a printed message, so the caller decides how
  to report errors and the classes stop writing to `std::cout`.
- Separate reporting from the system: a `Report` class that reads the data and formats it, so
  `RentalSystem` is not both the rule-keeper and the printer.
- Add persistence, so data survives between runs.
- Allow more than one active rental per customer, if the business rule changed — that would
  mean replacing the `bool` with a list of open rental ids.

### 18. Why didn't you use a database / file storage?

The lab is about class design, not storage. Adding a database or file format would introduce a
lot of code that has nothing to do with the OOP concepts being assessed, and would make the
design harder to read. The data lives in memory for one run of the program, which is enough to
demonstrate every requirement.

### 19. Why aren't there any exceptions?

Every invalid operation here is an ordinary, expected outcome — a customer asking for a car
that is already out is not an exceptional condition, it is Tuesday. So those cases return
`false` and print a clear reason. That keeps the control flow visible and easy to follow. If
this grew into a library used by other code, I would return a status/result type rather than
printing.

### 20. What is `override` doing, and why did you write it?

It tells the compiler "this function is meant to replace a virtual function in the base class."
If the signature does not match one — a typo, a missing `const` — the code fails to compile
instead of quietly creating a brand-new function that never gets called. It is a free
safety check.

### 21. Why is the `Vehicle` constructor `protected`?

Because `Vehicle` should never be created on its own, only as part of a `Car`, `Motorbike` or
`Truck`. `protected` says exactly that: derived classes can call it, outside code cannot. The
class is already abstract, so this mainly documents the intent.

Note also that the base class's data is **private**, not protected — so `Truck` cannot touch
`dailyRate` directly. It calls `getDailyRate()`. Derived classes are still outside code as far
as the base class's invariants are concerned.

### 22. Where is the cost calculated, and why is it stored in the `Rental`?

It is calculated by the vehicle (`calculateCost()`), called once from `rentVehicle()` at the
moment the rental is created, and the resulting number is stored in the `Rental`. That mirrors
real life — the price is agreed when the vehicle is taken — and it means a later change to a
daily rate cannot silently rewrite the cost of a rental that already happened.
