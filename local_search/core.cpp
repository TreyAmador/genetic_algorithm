#include "core.h"
#include "search.h"
#include "utilities.h"



namespace {
	const int CONFIG_SIZE = 21;
	const int TOTAL_TRIALS = 100;


	std::vector<int> test_config = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	};
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {

	int trial = 0;
	LocalSearch search(CONFIG_SIZE);
	while (!this->is_complete(trial)) {
		std::vector<int> config = search.generate_config(CONFIG_SIZE);
		std::vector<int> optimal = search.climb(config);
		std::cout <<
			search.config_score(config) << " " <<
			search.config_score(optimal) << "\n" << std::endl;
		++trial;
	}
	return 0;
}



inline bool Core::is_complete(int trial) {
	return trial >= TOTAL_TRIALS;
}
