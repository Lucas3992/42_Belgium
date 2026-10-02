#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <ctime>
# include <cstdlib>

template <typename T>
class Array {
    private:
        T* _array;
        unsigned int _size;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array& other);
        Array& operator=(const Array& other);
        ~Array();

        T& operator[](unsigned int index);
        const T& operator[](unsigned int index) const;
        size_t size() const;

		class ArrayException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

# include "Array.tpp"

#endif