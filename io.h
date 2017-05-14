#ifndef CONSOLE_H_
#define CONSOLE_H_
#include <iostream>
#include <fstream>
#include <string>
#include "evolution.h"
#include "data.h"


class IO {


public:
	IO(const std::string& filepath);
	~IO();

	void init_filestream(const std::string& filepath);
	void user_prompt(int queens, int trials);
	void iteration(Population& fittest);
	void summary(long long mean, Population& fittest, int generations);
	void print_population(Population& fittest);

	int terminate(bool success);
	

private:
	std::fstream fs_;
	size_t fit_organisms_;


};


#endif
