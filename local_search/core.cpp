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

	LocalSearch search(CONFIG_SIZE);
	int max_score = search.get_max(), trial = 0, success = 0;
	while (!this->is_complete(trial)) {
		std::vector<int> config = search.generate_config(CONFIG_SIZE);
		std::vector<int> optimal = search.climb(config);
		int score = this->iteration_summary(search, config, optimal);
		if (this->goal_config(max_score,score))
			++success;
		++trial;
	}
	return this->complete(success, TOTAL_TRIALS);
}


inline bool Core::is_complete(int trial) {
	return trial >= TOTAL_TRIALS;
}


inline bool Core::goal_config(int max, int score) {
	return max == score;
}


int Core::iteration_summary(
	LocalSearch& search,
	std::vector<int>& config,
	std::vector<int>& optimal) 
{
	int score = search.config_score(optimal);
	util::print_1d(config);
	util::print_1d(optimal, " ", " ");
	std::cout << "Score: " << score << "\n" << std::endl;
	return score;
}


int Core::complete(int success, int total) {
	std::cout << "\n\n" <<
		"Successes: " <<
		static_cast<double>(success) / total << "\n" << std::endl;
	return 0;
}


