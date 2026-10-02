#include "Base.hpp"

Base::~Base() {}

Base* generate() {
    switch (std::rand() % 3) {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}

void identify(Base* p) {
    if (!p)
        return;
    if (dynamic_cast<A*>(p)) {
        std::cout << "A\n";
        return;
    }
    if (dynamic_cast<B*>(p)) {
        std::cout << "B\n";
        return;
    }
    if (dynamic_cast<C*>(p)) {
        std::cout << "C\n";
        return;
    }
}

void identify(Base& p) {
    try { dynamic_cast<A&>(p); std::cout << "A\n"; return; }
    catch (...) {}
    try { dynamic_cast<B&>(p); std::cout << "B\n"; return; }
    catch (...) {}
    try { dynamic_cast<C&>(p); std::cout << "C\n"; return; }
    catch (...) {}
}