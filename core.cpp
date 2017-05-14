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

		//auto init_trial = this->get_time();

		while (!this->enough_configs(fittest)) {

			//auto init_iter = this->get_time();
			//auto init_iter = std::chrono::high_resolution_clock::now().time_since_epoch();

			Population filial = evolution.reproduce(parental,POP_SIZE);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental))
				evolution.save_fittest(parental, fittest, POP_SIZE);
			io.iteration(fittest);

			//auto iter_delta = this->delta_time(init_iter);
			//std::cout << "Iteration time: " << iter_delta << std::endl;

		}

		//auto delta_trial = this->delta_time(init_trial);
		//std::cout << "Trial time: " << delta_trial << std::endl;

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




