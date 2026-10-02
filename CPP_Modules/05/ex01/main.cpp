#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    Bureaucrat d("Dede la deconne", 150);
    Form a("F#738.1.a", 150, 150);
    Form b("F#738.1.b", 149, 149);

    try {
        d.signForm(a);
        d.signForm(b);
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}