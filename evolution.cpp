#include <algorithm>
#include <iostream>
#include <numeric>
#include "evolution.h"
#include "utilities.h"


Evolution::Evolution(int num_genes) : 
	genome_size_(num_genes), genome_(num_genes),
	mutation_(std::mt19937(std::random_device{}()))
{
	std::iota(genome_.begin(), genome_.end(), 0);
}


Evolution::~Evolution() {
	this->clear_genes();
}


Population Evolution::reproduce(int size) {
	Population population(
		size, std::vector<int>(genome_size_));
	for (size_t i = 0; i < population.size(); ++i) {
		util::shuffle(genome_);
		for (size_t j = 0; j < population[i].size(); ++j)
			population[i][j] = genome_[j];
	}
	return population;
}


void Evolution::crossover(Population& population) {
	for (size_t i = 0; i < population.size()-1; i += 2)
		for (int bp = 0; bp <= this->base_pair(); ++bp)
			util::swap(population[i][bp], population[i+1][bp]);
}


void Evolution::mutate(Population& population, int mutations) {
	for (size_t i = 0; i < population.size(); ++i)
		for (int m = 0; m < mutations; ++m)
			this->snp(population[i][this->base_pair()]);
}


int Evolution::fitness(Population& population) {



	return 0;
}


int Evolution::base_pair() {
	return mutation_() % genome_size_;
}


void Evolution::snp(int& bp) {
	bp = (mutation_()+bp)%genome_size_;
}


void Evolution::clear_genes() {
	genome_.clear();
	genome_.shrink_to_fit();
}




