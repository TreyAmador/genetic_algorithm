#pragma once
#include <iostream>
#include <vector>
#include <string>


namespace util {

	template <class T>
	void print_1d(
		std::vector<T>& vec,
		std::string sep = " ", std::string end = "\n")
	{
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << sep;
		std::cout << end;
	}

	template <class T>
	void clear_vec(std::vector<T>& vec) {
		vec.clear();
		vec.shrink_to_fit();
	}


	template <class T>
	std::vector<T> copy_vec(std::vector<T>& source) {
		std::vector<T> target(source.size());
		for (size_t i = 0; i < source.size(); ++i) {
			target[i] = source[i];
		}
		return target;
	}



}

