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
	for (size_t i = 0; i < population.size() - 1; i += 2) {
		int basepair = this->base_pair();
		for (int bp = 0; bp <= basepair; ++bp) {
			util::swap(population[i][bp], population[i + 1][bp]);
		}
	}
}


void Evolution::mutate(Population& population, int mutations) {
	for (size_t i = 0; i < population.size(); ++i)
		for (int m = 0; m < mutations; ++m)
			this->snp(population[i][this->base_pair()]);
}


int Evolution::fitness(Population& population) {
	int best_fitness = 0;
	for (size_t i = 0; i < population.size(); ++i) {
		int curr_fitness = this->fitness(population[i]);
		if (curr_fitness < best_fitness)
			best_fitness = curr_fitness;
	}
	return best_fitness;
}


int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.size(); ++i) {
		this->direction(organism, fit_scr, i, MOVE::STILL);
		this->direction(organism, fit_scr, i, MOVE::UP);
		this->direction(organism, fit_scr, i, MOVE::DOWN);
	}
	return fit_scr;
}


// this should move along the board
// checking left, up-left, down-left
// for potential collisions
void Evolution::direction(
	Organism& organism, int& fitness,
	int col, int hrz)
{
	int max = hrz == MOVE::UP ? genome_size_ : -1;
	int row = organism[col];
	for (size_t c = col; c < organism.size() && row != max; ++c, row += hrz) {

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




