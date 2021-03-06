#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>
#include <random>


namespace util {

	
	template <class T>
	void print_1d(
		std::vector<T>& vec, 
		std::string sep = " ", std::string end="\n")
	{
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << sep;
		std::cout << end;
	}


	template <class T>
	void print_2d(
		std::vector<std::vector<T> >& vec, 
		std::string sep=" ", std::string end="\n\n") 
	{
		for (size_t i = 0; i < vec.size(); ++i) {
			util::print_1d(vec[i],sep);
		}
		std::cout << end;
	}


	template <class T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}


	template <class T>
	void shuffle(std::vector<T>& vec) {
		std::shuffle(vec.begin(), vec.end(), 
			std::mt19937{ std::random_device{}()});
	}


	// not good for deep copy
	template <class T>
	std::vector<T> shuffled(std::vector<T>& vec) {
		std::vector<T> res(vec);
		std::shuffle(res.begin(), res.end(),
			std::mt19937{ std::random_device{}() });
		return res;
	}


	template <class T>
	void clear_vec(std::vector<T>& vec) {
		vec.clear();
		vec.shrink_to_fit();
	}


	struct IndexElement {
		int index;
		int element;
	};


}


#endif
