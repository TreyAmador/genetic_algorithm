#include <algorithm>
#include <iostream>
#include "search.h"
#include "utilities.h"


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
	std::vector<int> config(size);
	std::generate(config.begin(), config.end(), 
		[size]{ return rand() % size; });
	return config;
}


std::vector<int> LocalSearch::climb_right(std::vector<int>& config) {
	std::vector<int> 
		current = util::copy_vec(config),
		iter_neighbor = util::copy_vec(config);
	do {
		iter_neighbor = util::copy_vec(current);
		for (size_t i = 0; i < current.size(); ++i) {
			std::vector<int> neighbor_up = util::copy_vec(current);
			std::vector<int> neighbor_down = util::copy_vec(current);
			neighbor_up[i] = ++neighbor_up[i] % config_size_;
			neighbor_down[i] = --neighbor_down[i] > 0 ? neighbor_down[i] : config_size_;
			if (this->config_score(neighbor_up) >= this->config_score(current))
				current = neighbor_up;
			if (this->config_score(neighbor_down) >= this->config_score(current))
				current = neighbor_down;
		}
	} while (this->config_score(current) > this->config_score(iter_neighbor));
	return current;
}


std::vector<int> LocalSearch::climb_up(std::vector<int>& config) {
	std::vector<int> current = util::copy_vec(config);
	for (size_t i = 0; i < current.size(); ++i) {
		std::vector<int> neighbor_up = util::copy_vec(current);
		std::vector<int> neighbor_down = util::copy_vec(current);
		do {
			neighbor_up[i] = ++neighbor_up[i] % config_size_;
			neighbor_down[i] = --neighbor_down[i] > 0 ? neighbor_down[i] : config_size_;
			if (this->config_score(neighbor_up) > this->config_score(current))
				current = neighbor_up;
			if (this->config_score(neighbor_down) > this->config_score(current))
				current = neighbor_down;
		} while (this->config_score(current) < this->config_score(neighbor_up));
	}
	return current;
}



std::vector<int> LocalSearch::climb(std::vector<int>& config) {
	std::vector<int> current = util::copy_vec(config);
	for (int i = 0; i < 10; ++i) {		// this should be a do while to test if improved iteration
		for (int c = 0; c < config_size_; ++c) {
			std::vector<int> neighbor = util::copy_vec(current);
			for (int r = 0; r < config_size_; ++r) {
				neighbor[c] = r;
				if (this->config_score(neighbor) > this->config_score(current)) {
					current = neighbor;
				}
			}
		}
	}
	return current;
}


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





