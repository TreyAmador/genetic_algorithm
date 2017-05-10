#include <vector>
#include "utilities.h"
#include "core.h"
#include "io.h"


namespace {
	const int NUM_GENES = 21;
	const int POP_SIZE = 100;
	const int DESIRED_CONFIGS = 3;
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	
	IO io("");
	Evolution evolution(NUM_GENES);
	while (this->next_trial()) {
		io.user_prompt(NUM_GENES);
		Population fittest;
		Population parental = evolution.produce(POP_SIZE);
		while (!this->enough_configs(fittest)) {
			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental))
				evolution.save_fittest(parental, fittest, POP_SIZE);
			io.iteration(fittest);
		}
		io.summary(fittest);
	}

	return io.terminate(true);
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


//int Core::complete(bool success) {
//	std::cout << 
//		"The simulation has ended." << "\n" << std::endl;
//	return success ? 1 : -1;
//}



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


