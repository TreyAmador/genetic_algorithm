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
	int trial = 0;
	
	int sum_opt = 0;
	

	/*
	int iter = 0;

	while (true) {
		std::vector<int> config = search.generate_config(CONFIG_SIZE);
		std::vector<int> optimal = search.climb_up(config);
		if (search.config_score(optimal) == 210) {
			std::cout << std::endl;
			util::print_1d(optimal);
			std::cout << "\n" << "Success!" << std::endl;
			std::cout << "After only " << iter << " iterations!" << "\n" << std::endl;
		}

		std::cout << ".";

		++iter;
	}
	*/


	
	while (!this->is_complete(trial)) {

		std::vector<int> config = search.generate_config(CONFIG_SIZE);
		
		//std::vector<int> optimal = search.climb_up(config);
		
		//std::vector<int> optimal = search.climb_right(config);

		std::vector<int> optimal = search.climb(config);


		util::print_1d(optimal);
		std::cout << 
			search.config_score(config) << " " << 
			search.config_score(optimal) << "\n" << std::endl;

		sum_opt += search.config_score(optimal);


		++trial;
	}
	

	std::cout << "\n\nAverage: " << sum_opt / TOTAL_TRIALS << "\n" << std::endl;




	return 0;
}



inline bool Core::is_complete(int trial) {
	return trial >= TOTAL_TRIALS;
}
