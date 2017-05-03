#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <iostream>
#include <random>


namespace UTIL {


	/*
	int* copy_ptr(int* ptr, int size) {
		int* res = new int[size];
		for (int i = 0; i < size; ++i)
			res[i] = ptr[i];
		return res;
	}
	*/


	
	template <class T>
	void print_1d(std::vector<T>& vec) {
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}


	template <class T>
	void print_2d(std::vector<std::vector<T> >& vec) {
		for (size_t i = 0; i < vec.size(); ++i) {
			UTIL::print_1d(vec[i]);
		}
		std::cout << std::endl;
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



}


#endif
