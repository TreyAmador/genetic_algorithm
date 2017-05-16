#include <algorithm>
#include <numeric>
#include <iostream>
#include <chrono>
#include "search.h"
#include "utilities.h"


namespace {
	const int ALLOWABLE_ATTEMPTS = 2;
}


enum MOVE {
	UP = 1,
	DOWN = -1,
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};


LocalSearch::LocalSearch(int size) :
	config_size_(size), least_fit_(size*(size-1)/2)
{}


LocalSearch::~LocalSearch() {

}


std::vector<int> LocalSearch::generate_config(int size) {
	std::mt19937 mt(static_cast<unsigned int>(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::vector<int> config(size);
	std::generate(config.begin(), config.end(), 
		[&mt,size]{ return mt() % size; });
	return config;
}


std::vector<int> LocalSearch::climb(std::vector<int>& config) {
	std::vector<int> current = util::copy_vec(config);
	int current_max = this->config_score(current);
	int attempts = 0;
	do {
		std::vector<int> iteration = util::copy_vec(current);
		for (int c = 0; c < config_size_; ++c) {
			std::vector<int> neighbor = util::copy_vec(current);
			for (int r = 0; r < config_size_; ++r) {
				neighbor[c] = r;
				if (this->config_score(neighbor) >= this->config_score(current))
					current = neighbor;
			}
		}
		attempts = this->improved(current, iteration) ? 0 : ++attempts;
	} while (attempts < ALLOWABLE_ATTEMPTS);
	return current;
}



/*
std::vector<int> LocalSearch::climb(std::vector<int>& config) {
	std::vector<int> current = util::copy_vec(config);
	std::vector<int> iteration;
	do {
		iteration = current;
		for (int c = 0; c < config_size_; ++c) {
			std::vector<int> neighbor = util::copy_vec(current);
			for (int r = 0; r < config_size_; ++r) {
				neighbor[c] = r;
				if (this->config_score(neighbor) > this->config_score(current))
					current = neighbor;
			}
		}
	} while (!util::equal(current,iteration));
	return current;
}
*/

/*
std::vector<int> LocalSearch::climb(std::vector<int>& config) {
	
	std::vector<int> current = util::copy_vec(config);
	std::vector<int> iteration;
	int iter = 0;
	do {
		iteration = current;
		for (int c = 0; c < config_size_; ++c) {
			std::vector<int> neighbor = util::copy_vec(current);
			for (int r = 0; r < config_size_; ++r) {
				neighbor[c] = r;
				if (this->config_score(neighbor) > this->config_score(current))
					current = neighbor;
			}
		}
		//if (this->config_score(current) <= this->config_score(iteration))
		//	++iter;
		//else
		//	iter = 0;

		if (util::equal(current, iteration))
			++iter;
		else
			iter = 0;

	} while (iter < 2);
	return current;
}
*/


/*
std::vector<int> LocalSearch::climb(std::vector<int>& config) {
	std::vector<int> current = util::copy_vec(config);
	std::vector<int> iteration;
	for (int i = 0; i < 3 && this->config_score(current) < least_fit_; ++i) {
		do {
			iteration = util::copy_vec(current);
			for (int c = 0; c < config_size_; ++c) {
				std::vector<int> neighbor = util::copy_vec(current);
				for (int r = 0; r < config_size_; ++r) {
					neighbor[c] = r;
					if (this->config_score(neighbor) >= this->config_score(current))
						current = neighbor;
				}
			}
		} while (this->config_score(current) > this->config_score(iteration));
	}
	return current;
}
*/


int LocalSearch::config_score(std::vector<int>& config) {
	int fit_scr = 0;
	for (size_t i = 0; i < config.size(); ++i) {
		this->collisions(config, fit_scr, i, MOVE::STILL);
		this->collisions(config, fit_scr, i, MOVE::UP);
		this->collisions(config, fit_scr, i, MOVE::DOWN);
	}
	return least_fit_ - fit_scr;
}


void LocalSearch::collisions(
	std::vector<int>& config, int& fit_scr,
	size_t column, int hrz)
{
	size_t col = column;
	int row = config[col];
	int extr = hrz == MOVE::UP ? config_size_ : -1;
	while (col < config.size() && row != extr) {
		if (config[col] == row && col != column)
			++fit_scr;
		++col;
		row += hrz;
	}
}


bool LocalSearch::improved(
	std::vector<int>& current,
	std::vector<int>& neighbor)
{
	return this->config_score(current) > this->config_score(neighbor);
}


