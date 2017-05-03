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
		auto population = evolution.reproduce(2);
		
		
		//Organism organism = population[0];
		
		Organism organism = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
		//Organism organism(20, 5);
		util::print_1d(organism,"\n\n");

		int fitness = 0;
		
		evolution.direction(organism,fitness,0,0);
		std::cout << fitness << std::endl;
		evolution.direction(organism, fitness, 0, 1);
		std::cout << fitness << std::endl;
		evolution.direction(organism, fitness, 0, -1);
		std::cout << fitness << std::endl;





		//while (this->unsolved()) {
			//evolution.crossover(population);
			//evolution.mutate(population, MUTATIONS);

			//util::print_2d(population);
			//std::cout << "\n" << std::endl;

			//evolution.fitness(population);

			//Organism organism = population[0];
			//util::print_1d(organism);
			//std::cout << std::endl;

			//evolution.fitness(organism);

			//std::cout << std::endl;
		
		//}
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



