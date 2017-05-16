#pragma once
#include <vector>
#include <random>


class LocalSearch {


public:
	LocalSearch(int size);
	~LocalSearch();

	std::vector<int> climb(std::vector<int>& config);

	std::vector<int> generate_config(int size);
	int config_score(std::vector<int>& config);
	void collisions(
		std::vector<int>& config, int& fit_scr,
		size_t column, int hrz);
	bool improved(
		std::vector<int>& current,
		std::vector<int>& neighbor);
	//bool improved(int current_max,std::vector<int>& neighbor);


private:
	int config_size_;
	int least_fit_;


};