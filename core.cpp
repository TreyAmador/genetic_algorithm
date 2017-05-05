#include <vector>
#include "evolution.h"
#include "utilities.h"
#include "core.h"


namespace {
	// some of these should be in evolution?
	const int NUM_GENES = 21;
	const int POP_SIZE = 10000;
	const int CROSSES = 10;
	const int INSTABILITY = 1;
	const int MUTATIONS = 1;

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
		Population parental = evolution.produce(POP_SIZE, FIT_THRESHOLD);
		while (this->unsolved()) {
			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.cull(filial, 20);

			std::cout << "this many people " << filial.size() << std::endl;

			util::print_1d(filial[0].genome_);
			std::cout << "fitness: " << filial[0].fitness_ << "\n\n";
			
		}
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


bool Core::unsolved() {
	static int trials = 0;
	if (trials++ < 1)
		return true;
	else
		return false;
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


