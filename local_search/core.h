#pragma once
#include "search.h"


class Core {




public:
	Core();
	~Core();

	int run();


private:
	inline bool is_complete(int trials);
	inline bool goal_config(int max, int score);

	int iteration_summary(
		LocalSearch& search,
		std::vector<int>& config,
		std::vector<int>& optimal);

	int complete(int success, int total);


};

