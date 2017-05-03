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


void Evolution::crossover(std::vector<int>& x, std::vector<int>& y, int crosses) {

}


void Evolution::mutate(std::vector<int>& organism, int mutations) {

}



void Evolution::clear_genes() {
	genome_.clear();
	genome_.shrink_to_fit();
}



