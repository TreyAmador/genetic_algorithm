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
			Population filial = evolution.reproduce(parental,POP_SIZE);
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

