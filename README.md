# Object-Oriented Programming in C++

My 2nd semester OOP lab work in C++. All 13 labs are in the [LAB-TASKS/](LAB-TASKS/) folder. Every task is a separate `.cpp` file with its own `main()`, so each one runs on its own.

## How to Run

```bash
g++ "LAB-TASKS/LAB-05/Task 1.cpp" -o task
./task
```

## What I Did in Each Lab

**[LAB-01](LAB-TASKS/LAB-01/) — Structures**
Made a student struct, used an array of structures for multiple students, and created a struct on the heap using `new` and `delete`.

**[LAB-02](LAB-TASKS/LAB-02/) — Classes and Header Files**
Wrote 5 classes (Student, Rectangle, Voter, Temperature, Calculator), each in its own header file, and defined member functions outside the class using `::`.

**[LAB-03](LAB-TASKS/LAB-03/) — Encapsulation**
Made a Product class with private data and setters that check the input, so an empty name or a negative price gets rejected.

**[LAB-04](LAB-TASKS/LAB-04/) — Constructors and Destructors**
Used a parameterized constructor for a bank account, a default constructor for an employee, constructor overloading for a rectangle, and a destructor for a locker.

**[LAB-05](LAB-TASKS/LAB-05/) — Inheritance**
Practiced all four types: single (Person → Student), multilevel (Person → Employee → Manager), multiple (Printer + Scanner → Photocopier), and hierarchical (Employee → Developer, Designer).

**[LAB-06](LAB-TASKS/LAB-06/) — Constructors in Inheritance**
Checked the order in which constructors and destructors are called in a hierarchy, passed values to the parent constructor, and used a virtual destructor with heap memory.

**[LAB-07](LAB-TASKS/LAB-07/) — Composition and Aggregation**
Made a Calculator that owns a Display object (composition), and two Student objects that share one Calculator through a pointer (aggregation).

**[LAB-08](LAB-TASKS/LAB-08/) — Virtual Functions**
Made a shape base class with a virtual `area()` and overrode it in rectangle and circle, then called both through base class pointers.

**[LAB-09](LAB-TASKS/LAB-09/) — Polymorphism and Operator Overloading**
Calculated salary differently for permanent and contract employees using virtual functions, and overloaded the `==` operator to compare two distances.

**[LAB-10](LAB-TASKS/LAB-10/) — File Handling**
Wrote to a file, read it back, appended to it, counted the lines in it, copied one file into another, and saved student records.

**[LAB-11](LAB-TASKS/LAB-11/) — Friend Functions**
Used a friend function to print the private `length` of a Box object from outside the class.

**[LAB-12](LAB-TASKS/LAB-12/) — Friend Functions**
Used a friend function that takes two Distance objects, adds their feet and inches, and converts the extra inches into feet.

**[LAB-13](LAB-TASKS/LAB-13/) — Templates**
Wrote function templates to print a value twice and to find the minimum of two values, and class templates (Pair and Calculator) that work with int, double and string.

## Topics Covered

Structures, classes and objects, header files, encapsulation, abstraction, constructors and destructors, inheritance, polymorphism, virtual functions, operator overloading, composition and aggregation, friend functions, file handling, and templates.

## Author

**Absar Ali** — 2nd Semester, Object-Oriented Programming (C++)
