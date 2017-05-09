#include <vector>
#include "utilities.h"
#include "core.h"


namespace {
	// some of these should be in evolution?
	const int NUM_GENES = 21;
	const int POP_SIZE = 100;
	const int CROSSES = 10;
	const int INSTABILITY = 1;
	const int MUTATIONS = 1;

	const int DESIRED_CONFIGS = 3;
	const int FIT_THRESHOLD = 20;

	std::vector<int> test_genome = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	};

	// testing structures
	// Organism organism = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	// Organism organism(NUM_GENES, 5);
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	
	Evolution evolution(NUM_GENES);
	while (this->next_trial()) {
		Population fittest;
		Population parental = evolution.produce(POP_SIZE);
		while (!this->enough_configs(fittest)) {
			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental)) {
				evolution.get_fittest(parental, fittest, POP_SIZE);
				std::cout << "\n\nFittest added to set\n\n" << std::endl;
			}
			std::cout << ".";
		}
		std::cout << "\n\n\nFittest Population:\n" << std::endl;
		evolution.print_population(fittest);
	}



	return this->complete(true);
}


bool Core::next_trial() {
	static int trials = 0;
	if (trials++ < 1)
		return true;
	else
		return false;
}


inline bool Core::enough_configs(Population& fittest) {
	return fittest.size() >= DESIRED_CONFIGS;
}


int Core::complete(bool success) {
	std::cout << 
		"The simulation has ended." << "\n" << std::endl;
	return success ? 1 : -1;
}



void crossover_test() {

	/*
	std::vector<int> source01 = { 0,1,2,3,4,5,6,7,8,9 };
	std::vector<int> source02 = { 10,11,12,13,14,15,16,17,18,19 };
	int span = 4;
	std::vector<int> target(10);
	std::copy(source01.begin(), source01.begin() + span, target.begin());
	std::copy(source02.begin() + span, source02.end(), target.begin() + span);
	util::print_1d(source01);
	util::print_1d(source02);
	util::print_1d(target);
	*/


	/*
	Organism a, b;
	for (size_t i = 0; i < test_genome.size(); ++i) {
		a.genome_.push_back(i);
		b.genome_.push_back(i+100);
	}
	Organism offspring;
	offspring.genome_.resize(test_genome.size());
	evolution.crossover(a, b, offspring);
	util::print_1d(offspring.genome_);
	*/


}


