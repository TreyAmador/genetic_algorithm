#include <algorithm>
#include <iostream>
#include <numeric>
#include <chrono>
#include "evolution.h"
#include "utilities.h"


namespace {
	const int SENTINEL = -1;
}


// fittest organisms at top of heirarchy
bool organism_sort(Organism& a, Organism& b) {
	return a.fitness_ > b.fitness_;
}


bool organism_search(Organism& a, Organism& b) {
	return a.fitness_ > b.fitness_;
}


Evolution::Evolution(int num_genes) : 
	genome_size_(num_genes),
	least_fit_(this->least_fit(num_genes)),
	mutation_(this->mt19937_seeded())
{}


Evolution::~Evolution() {
	
}


Population Evolution::produce(size_t pop_size, int fit_thr) {
	Population population;
	while (population.size() < pop_size)
		population.push_back(this->generate_organism(genome_size_));
	this->sort_population(population);
	return population;
}


Population Evolution::reproduce(Population& population) {
	Population filial;
	int heirarchy = population.size() / 10;
	for (size_t m = 0; m < heirarchy; ++m)
		for (size_t f = heirarchy; f < population.size(); ++f)
			filial.push_back(this->crossover(population[m], population[f]));
	return filial;
}



/*
Population Evolution::reproduce(Population& parental) {
	Population filial;
	for (size_t i = 0; i < parental.size() - 1; i += 2)
		filial.push_back(this->crossover(parental[i], parental[i+1]));
	return filial;
}
*/


Organism Evolution::crossover(Organism& male, Organism& female) {
	Organism offspring;
	offspring.genome_.resize(genome_size_);
	if (mutation_() % 2)
		this->crossover(male, female, offspring);
	else
		this->crossover(female, male, offspring);
	return offspring;
}


void Evolution::crossover(
	Organism& parent_a,
	Organism& parent_b,
	Organism& offspring)
{
	int bp = this->base_pair();
	this->crossover(parent_a, offspring, 0, bp);
	this->crossover(parent_b, offspring, bp, offspring.genome_.size());
}


void Evolution::crossover(
	Organism& parent,
	Organism& offspring,
	int beg, int end)
{
	std::copy(
		parent.genome_.begin()+beg,
		parent.genome_.begin()+end,
		offspring.genome_.begin()+beg);
}


// test this
void Evolution::mutate(Population& pop) {
	for (auto p = pop.begin(); p != pop.end(); ++p) {
		if (this->is_mutable())
			this->snp(p->genome_[this->base_pair()]);
		p->fitness_ = this->fitness(*p);
	}
	this->sort_population(pop);
}


void Evolution::replenish(Population& parental, Population& filial, int size) {
	this->clear_population(parental);
	parental.resize(size);
	for (int i = 0; i < size/2; ++i)
		parental[i] = filial[i];
	for (int i = size/2; i < size; ++i)
		parental[i] = this->generate_organism(genome_size_);
	this->clear_population(filial);
	this->sort_population(parental);
}


void Evolution::cull(Population& pop, int threshold) {
	int index = SENTINEL;
	for (size_t i = 0; i < pop.size() && index == SENTINEL; ++i)
		if (pop[i].fitness_ > threshold)
			index = i;
	if (index != SENTINEL)
		pop.erase(pop.begin()+index, pop.end());

	//pop.erase(pop.begin(),pop.begin()+(pop.size()/threshold));


	//auto iter = std::lower_bound(pop.begin(), pop.end(), organism_search);
	//if (iter != pop.end()) {
	//	util::print_1d(iter->genome_);
	//	std::cout << "fitness fxn " << iter->fitness_ << std::endl;
	//}

}


int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.genome_.size(); ++i) {
		this->collisions(organism.genome_, fit_scr, i, MOVE::STILL);
		this->collisions(organism.genome_, fit_scr, i, MOVE::UP);
		this->collisions(organism.genome_, fit_scr, i, MOVE::DOWN);
	}
	return least_fit_-fit_scr;
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


inline void Evolution::sort_population(Population& pop) {
	std::sort(pop.begin(), pop.end(), organism_sort);
}


inline std::mt19937 Evolution::mt19937_seeded() {
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


inline int Evolution::base_pair() {
	return mutation_() % genome_size_;
}


inline void Evolution::snp(int& bp) {
	bp = (mutation_()+bp)%genome_size_;
}


inline bool Evolution::is_mutable() {
	return mutation_() % 3 == 0;
}


void Evolution::clear_population(Population& population) {
	for (size_t i = 0; i < population.size(); ++i)
		util::clear_vec(population[i].genome_);
	util::clear_vec(population);
}


void Evolution::print_population(Population& pop) {
	for (auto iter = pop.begin(); iter != pop.end(); ++iter) {
		util::print_1d(iter->genome_, " ", " ");
		std::cout << ", fitness: " << iter->fitness_ << "\n";
	}
}





/*
void Evolution::cull(Population& pop) {
	for (PopIter iter = pop.begin(); iter != pop.end(); ++iter)
		util::clear_vec(*iter);
	util::clear_vec(pop);
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


