#include "evolution.h"
#include "utilities.h"
#include "core.h"


namespace {
	// some of these should be in evolution?
	const int NUM_GENES = 21;
	const int POPULATION_SIZE = 2;
	const int CROSSES = 10;
	const int INSTABILITY = 1;
	const int MUTATIONS = 1;

	// testing structures
	// Organism organism = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	// Organism organism(20, 5);
}



Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	
	Evolution evolution(NUM_GENES);
	while (this->next_trail()) {
		Population population = evolution.reproduce(POPULATION_SIZE);
		
		Population fittest;
		
		while (this->unsolved()) {
			evolution.crossover(population);
			evolution.mutate(population, MUTATIONS);

			util::print_2d(population);
			

		}
	}

	return 0;
}


bool Core::next_trail() {
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



