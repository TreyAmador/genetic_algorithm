#pragma once
#include <vector>


class LocalSearch {


public:
	LocalSearch(int size);
	~LocalSearch();

	std::vector<int> climb_right(std::vector<int>& config);
	std::vector<int> climb_up(std::vector<int>& config);
	std::vector<int> climb(std::vector<int>& config);

	std::vector<int> generate_config(int size);
	int config_score(std::vector<int>& config);
	void collisions(
		std::vector<int>& config, int& fit_scr,
		size_t column, int hrz);


private:
	int config_size_;
	int least_fit_;



};