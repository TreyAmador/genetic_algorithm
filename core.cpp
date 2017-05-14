#include <vector>
#include "utilities.h"
#include "core.h"


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
	Data data;
	Evolution evolution(NUM_GENES);
	while (this->next_trial()) {
		
		
		//io.user_prompt(NUM_GENES);

		this->begin_trial(io, data, NUM_GENES);

		Population fittest;
		Population parental = evolution.produce(POP_SIZE);
		while (!this->enough_configs(fittest)) {
			
			this->begin_interation(data);

			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental))
				evolution.save_fittest(parental, fittest, POP_SIZE);
			
			//io.iteration(fittest);

			this->end_iteration(io, data, fittest);

		}

		this->end_trial(io, data, fittest);

		//io.summary(fittest);


	}
	return io.terminate(true);
}


void Core::begin_interation(Data& data) {
	//data.init_iter();
}


void Core::end_iteration(IO& io, Data& data, Population& population) {
	//long long delta = data.end_iter();
	//std::cout << delta << ", ";
	//io.iteration(population);
	std::cout << ".";
}


void Core::begin_trial(IO& io, Data& data, int size) {
	io.user_prompt(size);
	//data.init_trial();
}


void Core::end_trial(IO& io, Data& data, Population& population) {
	//long long delta = data.end_trial();
	//std::cout << "\n\n" << "Trial: " << delta << "\n\n" << std::endl;
	io.summary(population);
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

