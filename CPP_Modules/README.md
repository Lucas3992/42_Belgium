# CPP Modules

The goal of these modules is to introduce object-oriented programming through C++98, step by step, from basic classes up to templates and the Standard Template Library.

Each module (`00` to `09`) contains several exercises, each in its own `exNN` folder. The main difficulties are following the C++98 standard, designing classes in the Orthodox Canonical Form, avoiding memory leaks with `new`/`delete`, and using the right tool for the job (casts, templates, STL containers) instead of C-style habits.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build

Each exercise is compiled with its own Makefile:

```bash
cd 00/ex00
make
./<executable>
make fclean
```

Everything is compiled with `c++ -Wall -Wextra -Werror -std=c++98`.

## Modules

| Module | Topic | Exercises |
|---|---|---|
| 00 | Namespaces, classes, member functions, streams, initialization lists, `static`, `const` | Megaphone, PhoneBook (`ADD` / `SEARCH` / `EXIT`), recreating a lost `Account` class from a log file |
| 01 | Memory allocation, pointers and references, `switch` | Dynamic allocation exercises and string/file handling |
| 02 | Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form | Fixed-point number class and overloaded operators |
| 03 | Inheritance | `ClapTrap`, `ScavTrap`, `FragTrap` (multiple inheritance) |
| 04 | Subtype polymorphism, abstract classes, interfaces | Class hierarchies using virtual functions |
| 05 | Repetition and exceptions | Classes that throw and catch exceptions |
| 06 | C++ casts | `ScalarConverter` (char/int/float/double), `Serializer`, identifying a real type without `typeinfo` |
| 07 | Templates | `swap`/`min`/`max`, `iter`, and an `Array` class template |
| 08 | Templated containers, iterators, algorithms | `easyfind`, `Span`, `MutantStack` (an iterable `std::stack`) |
| 09 | STL | Exercises built around standard containers |

## Rules followed

- C++98 only, no external libraries.
- STL only allowed from modules 08 and 09.
- Classes in Orthodox Canonical Form from module 02, include guards in every header.
- No `using namespace` and no `friend`, unless stated otherwise.

## Skills

- Classes, encapsulation and inheritance (including multiple inheritance)
- Polymorphism and abstract classes
- Exceptions and memory management
- Templates, STL containers, iterators and algorithms
