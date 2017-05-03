#include "evolution.h"
#include "utilities.h"
#include "core.h"


namespace {
	// some of these should be in evolution?
	const int WIDTH = 20;
	const int HEIGHT = 20;
	const int NUM_GENES = 20;
	const int POPULATION_SIZE = 100;
	const int CROSSES = 10;
	const int INSTABILITY = 1;
	const int MUTATIONS = 5;
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	
	Evolution evolution(NUM_GENES);
	while (this->next_trail()) {
		auto population = evolution.reproduce(POPULATION_SIZE);
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



