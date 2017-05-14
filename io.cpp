#include "io.h"


IO::IO(const std::string& filepath) : 
	fit_organisms_(0) 
{
	this->init_filestream(filepath);
}


IO::~IO() {

}


void IO::init_filestream(const std::string& filepath) {
	//fs_.open(filepath);
	
}


void IO::user_prompt(int queens, int trials) {
	std::string any_key;
	std::cout << 
		"Welcome to the " << queens << 
		"-Queens problem solver, which will find " << trials << 
		" configurations using a genetic algorithm." << "\n" << std::endl;
}


void IO::iteration(Population& fittest) {
	if (fittest.size() > fit_organisms_)
		std::cout << "\n" << "You have " << ++fit_organisms_ <<
		" solved configurations" << std::endl;
	else
		std::cout << ".";
}


void IO::summary(long long mean, Population& fittest, int generations) {
	std::cout << "\n" <<
		"This required " << mean << 
		" milliseconds per trial on average." << "\n" <<
		"The average number of generations was " << generations << 
		" generations." << "\n\n" << std::endl;
	this->print_population(fittest);
}


int IO::terminate(bool success) {
	std::cout << "\n" << 
		"The simulation has terminated." << "\n" << std::endl;
	return success ? 1 : -1;
}


void IO::print_population(Population& fittest) {
	std::cout << 
		"The following configurations have no collisions: " << "\n" << std::endl;
	for (auto iter = fittest.begin(); iter != fittest.end(); ++iter) {
		for (size_t i = 0; i < iter->genome_.size(); ++i)
			std::cout << iter->genome_[i] << " ";
		std::cout << std::endl;
	}
}


