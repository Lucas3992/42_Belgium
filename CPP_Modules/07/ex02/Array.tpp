#include "Array.hpp"

template <typename T> Array<T>::Array() {
    _array = NULL;
    _size = 0;
}

template <typename T> Array<T>::Array(unsigned int n) {
    _size = n;
    _array = new T[n]();
}

template <typename T> Array<T>::Array(const Array& other) {
	_array = NULL;
	_size = other._size;
	*this = other;
}

template <typename T> Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] _array;
        _size = other._size;
        _array = new T[_size]();
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = other._array[i];
    }
	return *this;
}

template <typename T> Array<T>::~Array() {
    delete[] _array;
}

template <typename T> T& Array<T>::operator[](unsigned int index) {
    if (index >= _size)
        throw ArrayException();
    return _array[index];
}

template <typename T> const T& Array<T>::operator[](unsigned int index) const {
    if (index >= _size)
        throw ArrayException();
    return _array[index];
}

template <typename T> size_t Array<T>::size() const {
    return (size_t)_size;
}

template <typename T> const char* Array<T>::ArrayException::what() const throw() {
	return "Out of bounds";
}