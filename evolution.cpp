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


std::vector<std::vector<int> > Evolution::reproduce(int size) {
	std::vector<std::vector<int> > population(
		size, std::vector<int>(genome_size_));
	for (size_t i = 0; i < population.size(); ++i) {
		util::shuffle(genome_);
		for (size_t j = 0; j < population[i].size(); ++j)
			population[i][j] = genome_[j];
	}
	return population;
}


void Evolution::crossover(
	std::vector<std::vector<int> >& population,
	int swaps, int crosses)
{
	for (int c = 0; c < swaps; ++c)
		for (size_t i = 0; i < population.size()-1; i += 2)
			this->crossover(population[i], population[i + 1], crosses);
}


void Evolution::crossover(
	std::vector<int>& male,
	std::vector<int>& female,
	int crosses)
{
	for (int i = 0; i < crosses; ++i) {
		int bp = this->base_pair();
		util::swap(male[bp], female[bp]);
	}
}


void Evolution::mutate(
	std::vector<std::vector<int> >& population,
	int mutations)
{
	for (size_t i = 0; i < population.size(); ++i)
		this->mutate(population[i], mutations);
}


void Evolution::mutate(std::vector<int>& organism, int mutations) {
	for (int i = 0; i < mutations; ++i) {
		int bp = this->base_pair();
		this->snp(organism[bp]);
	}
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




