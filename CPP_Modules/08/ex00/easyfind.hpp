#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <iostream>
# include <vector>
# include <cstdlib>
# include <cmath>

template <typename T> 
typename T::iterator easyfind(T& container, int x) {
	typename T::iterator it = std::find(container.begin(), container.end(), x);
	if (it == container.end()) 
		throw std::runtime_error("Couldn't find");
	return it;
}

#endif