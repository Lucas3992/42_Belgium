#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# include <cstdlib>
# include <ctime>

template <typename T>
void iter(T* array, const size_t length, void (*f)(T&)) {
    for (size_t i = 0; i < length; i++)
        f(array[i]);
}

template <typename T>
void iter(const T* array, const size_t length, void (*f)(const T&)) {
    for (size_t i = 0; i < length; i++)
        f(array[i]);
}

#endif