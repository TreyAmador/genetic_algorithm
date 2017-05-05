#include <vector>
#include "evolution.h"
#include "utilities.h"
#include "core.h"


namespace {
	// some of these should be in evolution?
	const int NUM_GENES = 21;
	const int POP_SIZE = 1000;
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

		for (auto& p : parental) {
			util::print_1d(p.genome_);
			std::cout << "fitness: " << p.fitness_ << "\n\n";
		}

		//while (this->unsolved()) {
			
			

		//}
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
		"The trial has ended." << "\n" << std::endl;
	return success ? 1 : -1;
}


