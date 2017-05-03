#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include "evolution.h"
#include "utilities.h"


Evolution::Evolution(int num_genes) : 
	genome_size_(num_genes), genome_(num_genes)
{
	std::iota(genome_.begin(), genome_.end(), 0);
}


Evolution::~Evolution() {
	this->clear_genes();
}


std::vector<std::vector<int> > Evolution::reproduce(int size) {
	std::vector<std::vector<int> > population(
		size, std::vector<int>(genome_size_));
	for (size_t i = 0; i < population.size(); ++i) {
		UTIL::shuffle(genome_);
		for (size_t j = 0; j < population[i].size(); ++j)
			population[i][j] = genome_[j];
	}
	return population;
}


void Evolution::cross_population(
	std::vector<std::vector<int> >& population,
	int crosses, int magnitude)
{
	for (int i = 0; i < crosses; ++i) {
		int male = 0; // rand
		int female = 0; // rand
	}
}


void Evolution::crossover(std::vector<int>& male, std::vector<int>& female, int magnitude) {

}


void Evolution::mutate(std::vector<int>& organism, int mutations) {

}



void Evolution::clear_genes() {
	genome_.clear();
	genome_.shrink_to_fit();
}



