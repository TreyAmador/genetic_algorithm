#include <vector>
#include "utilities.h"
#include "core.h"


namespace {
	const int NUM_GENES = 21;
	const int POP_SIZE = 100;
	const int DESIRED_CONFIGS = 5;
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	IO io("");
	Data data;
	Evolution evolution(NUM_GENES);
	int generations = 0;
	while (this->next_trial()) {
		this->begin_trial(io, data, NUM_GENES,DESIRED_CONFIGS);
		Population fittest;
		Population parental = evolution.produce(POP_SIZE);
		while (!this->enough_configs(fittest)) {
			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental))
				evolution.save_fittest(parental, fittest, POP_SIZE);
			io.iteration(fittest);
			++generations;
		}
		this->end_trial(io, data, fittest, generations);
	}
	return io.terminate(true);
}


void Core::begin_trial(IO& io, Data& data, int size, int trials) {
	io.user_prompt(size, trials);
	data.init_trial();
}


void Core::end_trial(
	IO& io, Data& data, 
	Population& population, 
	int generations) 
{
	long long delta = data.end_trial();
	long long mean = (delta / 1000000) / DESIRED_CONFIGS;
	io.summary(mean,population,generations/DESIRED_CONFIGS);
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

