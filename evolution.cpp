#include <algorithm>
#include <iostream>
#include <numeric>
#include "evolution.h"
#include "utilities.h"


struct Fit {
	int max;
	int index;
};


Evolution::Evolution(int num_genes) : 
	genome_size_(num_genes), genome_(num_genes),
	least_fit_(num_genes*(num_genes-1)/2),
	mutation_(std::mt19937(std::random_device{}()))
{
	std::iota(genome_.begin(), genome_.end(), 0);

	std::cout << least_fit_ << "\n" << std::endl;
	std::cout << this->least_fit(num_genes) << "\n" << std::endl;

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



void Evolution::fitness(Population& population, Population& fittest) {

	util::IndexElement pair = { -1, -1 };
	



}


int Evolution::fitness(Population& population) {
	int best_fitness = 0;
	for (size_t i = 0; i < population.size(); ++i) {
		int curr_fitness = this->fitness(population[i]);
		if (curr_fitness < best_fitness) {
			best_fitness = curr_fitness;
		}
	}
	return best_fitness;
}


int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.size(); ++i) {
		this->collisions(organism, fit_scr, i, MOVE::STILL);
		this->collisions(organism, fit_scr, i, MOVE::UP);
		this->collisions(organism, fit_scr, i, MOVE::DOWN);
	}
	return fit_scr;
}


// TODO: revise to be more efficient
// second condition in if => init differently
void Evolution::collisions(
	Organism& org, int& fit_scr,
	size_t column, int hrz)
{
	size_t col = column;
	int row = org[col];
	int extr = hrz == MOVE::UP ? genome_size_ : -1;
	while (col < org.size() && row != extr) {
		if (org[col] == row && col != column)
			++fit_scr;
		++col;
		row += hrz;
	}
}


// could also be genes * ( genes - 1 ) / 2
int Evolution::least_fit(int genes) {
	int fit = 0;
	for (int i = 1; i < genes; ++i) {
		fit += i;
	}
	return fit;
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


