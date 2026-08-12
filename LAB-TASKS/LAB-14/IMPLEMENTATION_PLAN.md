# Implementation Plan — Vehicle Rental System (Lab 14)

This records how the lab was actually built, in order. Every box ticked below was really done;
nothing is ticked in advance.

---

## Phase 1 — Repository inspection

- [x] Listed the repository structure: `LAB-TASKS/LAB-01` … `LAB-TASKS/LAB-14`, plus the root
      `README.md`.
- [x] Confirmed `LAB-TASKS/LAB-14/` existed and was **empty**, so nothing had to be preserved
      or reused.
- [x] Looked at earlier labs (LAB-02, LAB-08, LAB-09) to see the existing style: single-file
      tasks, classes with private data, virtual functions already used in LAB-08/09.
- [x] Checked the toolchain: MinGW `g++ 6.3.0` is the only compiler installed.
- [x] Checked that `-std=c++17` is genuinely accepted by it (a bogus `-std=c++99` is rejected
      with an error, so the flag is real, not silently ignored).
- [x] Decided the consequence: stay on core C++ features that this compiler fully supports and
      that are equally valid C++17 — no `std::optional`, no structured bindings, no if-init.
- [x] Confirmed Labs 1–13 are to be treated as read-only. Nothing outside `LAB-14/` was
      touched at any point.

---

## Phase 2 — Design

- [x] Read the six functional requirements (R1–R6) and listed the decisions the assignment
      leaves open.
- [x] Decided the class hierarchy: `Vehicle` abstract, with `Car`, `Motorbike`, `Truck`
      derived — a real *is-a* relationship, not reuse.
- [x] Rejected the alternative "one class with a type string + all attributes", because it
      forces meaningless fields and an `if`-chain for pricing.
- [x] Decided pricing lives in `Vehicle::calculateCost()` as a pure virtual function, since
      the *vehicle type* is what makes the price differ.
- [x] Decided `RentalSystem` owns the fleet, the customers and every rental record, and is the
      only class that changes their state.
- [x] Decided `Rental` refers to its customer and vehicle by **id**, not by pointer, because
      the `std::vector<Customer>` moves its elements when it grows and a stored pointer would
      dangle.
- [x] Settled the final class list at seven, and checked that each one has a job that cannot
      be folded into another.

---

## Phase 3 — Design note

- [x] Wrote `DESIGN_NOTE.md` **before** writing any C++ code, as the assignment requires.
- [x] Covered all six required topics: vehicle type design, pricing design, ownership, class
      responsibilities, the exact runtime-polymorphism location, and deliberate exclusions.
- [x] Recorded the alternatives considered and why each was rejected.
- [x] Re-read it after the code was finished and confirmed it still matches the code
      (function names, file names, formulas and flag names all check out).

---

## Phase 4 — Class implementation

- [x] `include/Vehicle.h` + `src/Vehicle.cpp` — private data, protected constructor, virtual
      destructor, three pure virtual functions.
- [x] `include/Car.h` + `src/Car.cpp` — seats; plain daily rate.
- [x] `include/Motorbike.h` + `src/Motorbike.cpp` — engine cc; 10% discount when `days > 7`.
- [x] `include/Truck.h` + `src/Truck.cpp` — payload in tonnes; 20% surcharge.
- [x] `include/Customer.h` + `src/Customer.cpp` — id, name, active-rental flag.
- [x] `include/Rental.h` + `src/Rental.cpp` — the rental record, with `close()` instead of
      deletion.
- [x] Checked that every data member in every class is `private`.

---

## Phase 5 — Rental logic

- [x] `RentalSystem::addVehicle()` — takes ownership via `std::unique_ptr`, rejects duplicate
      vehicle ids.
- [x] `RentalSystem::registerCustomer()` — rejects duplicate customer ids, so ids stay unique.
- [x] `RentalSystem::rentVehicle()` — validates in order: duration ≥ 1 day, customer exists,
      vehicle exists, customer has no active rental, vehicle is available. Then calls
      `vehicle->calculateCost(days)` **through the base pointer**, stores the record, and sets
      both status flags together.
- [x] `RentalSystem::returnVehicle()` — closes the record (never deletes it), frees the
      vehicle, clears the customer's flag, and refuses cleanly if the vehicle is not out.
- [x] `printActiveRentals()`, `printRentalHistory()`, `printFleetAvailability()`,
      `printSummary()` — all `const`.
- [x] Confirmed there is no `new` or `delete` anywhere in the project.

---

## Phase 6 — Demonstration scenario

- [x] `main.cpp` builds a 4-vehicle fleet, registers 4 customers, processes 3 rentals (one per
      vehicle type so all three pricing rules show up), attempts 7 invalid operations, returns
      one vehicle, and prints the summary.
- [x] Fixed a flaw found while reading the first run's output: the "already rented vehicle"
      check was being masked, because the customer used for that test already had an active
      rental, so the *customer* rule fired first and the message proved the wrong thing. A
      fourth customer with no rental was added, and the check now demonstrates what it claims.
- [x] Added a rental by the same customer after the return, so the output proves the return
      really cleared the customer's active-rental flag — the identical request was refused
      earlier in the run.

---

## Phase 7 — Compilation

- [x] Built with:
      `g++ -std=c++17 -Wall -Wextra -I include main.cpp src/Vehicle.cpp src/Car.cpp src/Motorbike.cpp src/Truck.cpp src/Customer.cpp src/Rental.cpp src/RentalSystem.cpp -o rental`
- [x] Result: compiles successfully, exit code 0, and **zero warnings** under `-Wall -Wextra`.
- [x] Removed the built executable afterwards, since the repository tracks source only.

---

## Phase 8 — Testing

All of the following were run, not assumed.

- [x] **Program runs** to completion, exit code 0.
- [x] **R1 fleet** — 4 vehicles of 3 different types are held together and listed.
- [x] **R2 customers** — 4 registered; a duplicate id is refused.
- [x] **R3 rentals** — 3 rentals created; the vehicles are marked rented.
- [x] **R4 pricing**, verified against hand calculation:
      - Car 3 days → `45 × 3` = **135.00** ✔
      - Motorbike 10 days → `12 × 10 × 0.9` = **108.00** ✔
      - Truck 4 days → `150 × 4 × 1.2` = **720.00** ✔
      - Car 5 days → `30 × 5` = **150.00** ✔
- [x] **Motorbike discount boundary**, checked with a separate throwaway test program (kept
      out of this folder) that calls the classes directly:
      1 day → 12.00, **7 days → 84.00 (no discount)**, **8 days → 86.40 (discount applies)**,
      10 days → 108.00. All passed, so the rule is "more than 7 days", not "7 or more".
- [x] The same test also confirmed the calls give identical results **through a
      `std::unique_ptr<Vehicle>` base pointer**, i.e. the dispatch really is polymorphic.
- [x] **Validation** — each of these was refused with the correct, specific message:
      already-rented vehicle, customer with an active rental, 0 days, −4 days, unregistered
      customer, unknown vehicle id, duplicate customer id, returning a vehicle that is not out.
- [x] **R5 return** — the Corolla became available again, rental #1 shows as **CLOSED** in the
      history rather than disappearing, and the customer could then start a new rental.
- [x] **R6 summary** — active rentals list customer, vehicle, days and cost; availability shows
      1 available / 3 rented / 4 total, matching the per-vehicle status list.
- [x] **Warnings** — none under `-Wall -Wextra`.
- [x] **Memory** — no `new`/`delete` in the project; the fleet is held in
      `std::unique_ptr<Vehicle>` and `Vehicle` has a virtual destructor, so vehicles are freed
      correctly when the system goes out of scope. (No leak-detection tool such as Valgrind or
      ASan is available with this MinGW build, so this rests on inspection, not on a tool run.)

---

## Phase 9 — Final rubric review

- [x] **OOP design (×4)** — inheritance rests on a real *is-a* relationship; the polymorphism
      solves a real problem (mixed fleet, per-type pricing); seven coherent classes, none added
      for show.
- [x] **Design justification (×3)** — `DESIGN_NOTE.md` gives the reasoning and the rejected
      alternatives for every open decision, and matches the final code.
- [x] **Encapsulation & responsibility (×2)** — all data private; `RentalSystem` coordinates
      but does not calculate prices or know vehicle types, so it is not a God class.
- [x] **Working demo (×2)** — compiles, runs, and covers all six requirements plus the
      validation cases; the output is laid out in aligned tables.
- [x] **Code quality (×1)** — consistent naming, header/source separation, `const` correctness,
      `const&` parameters, no raw memory management, C++17 clean with no warnings.
- [x] **Repository safety** — verified with `git status` that the only changes are new files
      inside `LAB-TASKS/LAB-14/`; Labs 1–13 are untouched.
