#include <algorithm>
#include <iostream>
#include <numeric>
#include <chrono>
#include "evolution.h"
#include "utilities.h"


namespace {
	const int SENTINEL = -1;
}


struct Fit {
	int max;
	int index;
};


bool organism_sort(Organism& a, Organism& b) {
	return a.fitness_ < b.fitness_;
}


Evolution::Evolution(int num_genes) : 
	genome_size_(num_genes), genome_(num_genes),
	least_fit_(this->least_fit(num_genes)),
	mutation_(this->mt19937_seeded())
{
	std::iota(genome_.begin(), genome_.end(), 0);
}


Evolution::~Evolution() {
	this->clear_genes();
}


Population Evolution::produce(size_t pop_size, int fit_thr) {
	Population population;
	while (population.size() < pop_size) {
		Organism organism = this->generate_organism(genome_size_);
		if (organism.fitness_ < fit_thr)
			population.push_back(organism);
	}
	this->sort_population(population);
	return population;
}


/*
Organ Evolution::produce(size_t size, int fit_thr) {
	Organ organism;
	organism.genome_ = this->generate_organism(genome_size_);
	organism.fitness_ = this->fitness(organism);
	return organism;
}
*/

/*
void Evolution::crossover(Population& population) {
	for (size_t i = 0; i < population.size() - 1; i += 2) {
		int basepair = this->base_pair();
		for (int bp = 0; bp <= basepair; ++bp) {
			util::swap(population[i][bp], population[i + 1][bp]);
		}
	}
}
*/

/*
void Evolution::mutate(Population& population, int mutations) {
	for (size_t i = 0; i < population.size(); ++i)
		for (int m = 0; m < mutations; ++m)
			this->snp(population[i][this->base_pair()]);
}
*/


/*
void Evolution::fitness(Population& population, Population& fit_set) {
	util::IndexElement fit = { SENTINEL, least_fit_ };
	for (size_t i = 0; i < population.size(); ++i) {
		int fit_scr = this->fitness(population[i]);
		if (fit_scr < fit.element)
			fit = { static_cast<int>(i), fit_scr };
	}
	if (fit.index != SENTINEL)
		fit_set.push_back(population[fit.index]);
}
*/

/*
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
*/

/*
int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.size(); ++i) {
		this->collisions(organism, fit_scr, i, MOVE::STILL);
		this->collisions(organism, fit_scr, i, MOVE::UP);
		this->collisions(organism, fit_scr, i, MOVE::DOWN);
	}
	return fit_scr;
}
*/

int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.genome_.size(); ++i) {
		this->collisions(organism.genome_, fit_scr, i, MOVE::STILL);
		this->collisions(organism.genome_, fit_scr, i, MOVE::UP);
		this->collisions(organism.genome_, fit_scr, i, MOVE::DOWN);
	}
	return fit_scr;
}


// TODO: revise to be more efficient
// second condition in if => init differently
void Evolution::collisions(
	std::vector<int>& org, int& fit_scr,
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

/*
int Evolution::mean_fitness(Population& population) {
	int summation = 0, size = population.size();
	for (PopIter p = population.begin(); p != population.end(); ++p)
		summation += this->fitness(*p);
	return summation / size;
}
*/


void Evolution::sort_population(Population& population) {
	std::sort(
		population.begin(),
		population.end(),
		organism_sort);
}


Organism Evolution::generate_organism(int size) {
	Organism organism;
	organism.genome_ = this->generate_genome(size);
	organism.fitness_ = this->fitness(organism);
	return organism;
}


std::vector<int> Evolution::generate_genome(int size) {
	std::mt19937 mt = this->mt19937_seeded();
	std::vector<int> organism(size);
	std::generate(organism.begin(), organism.end(), 
		[&mt, size] { return mt() % size;});
	return organism;
}


std::mt19937 Evolution::mt19937_seeded() {
	std::mt19937 mt(static_cast<unsigned int>(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	return mt;
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


/*
void Evolution::cull(Population& pop) {
	for (PopIter iter = pop.begin(); iter != pop.end(); ++iter)
		util::clear_vec(*iter);
	util::clear_vec(pop);
}
*/

void Evolution::clear_genes() {
	genome_.clear();
	genome_.shrink_to_fit();
}


