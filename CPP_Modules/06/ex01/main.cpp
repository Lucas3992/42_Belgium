#include "Serializer.hpp"

int main() {
    Data d = {42};
    uintptr_t ser = Serializer::serialize(&d);
    Data* deser = Serializer::deserialize(ser);

    std::cout << "Original: " << &d << std::endl;
    std::cout << "Serialized: " << ser << std::endl;
    std::cout << "Deserialized: " << deser << std::endl;
    if (&d == deser)
        std::cout << "They're the same picture\n";

    return 0;
}