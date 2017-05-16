#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <chrono>


namespace util {

	template <class T>
	void print_1d(
		std::vector<T>& vec,
		std::string sep = " ", std::string end = "\n")
	{
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << sep;
		std::cout << end;
	}

	template <class T>
	void clear_vec(std::vector<T>& vec) {
		vec.clear();
		vec.shrink_to_fit();
	}

	template <class T>
	std::vector<T> copy_vec(std::vector<T>& source) {
		std::vector<T> target(source.size());
		for (size_t i = 0; i < source.size(); ++i) {
			target[i] = source[i];
		}
		return target;
	}

	template <class T>
	bool equal(std::vector<T>& a, std::vector<T>& b) {
		if (a.size() != b.size())
			return false;
		for (size_t i = 0; i < a.size(); ++i)
			if (a[i] != b[i])
				return false;
		return true;
	}

}


namespace {
	const int CONFIG_SIZE = 21;
	const int TOTAL_TRIALS = 100;
	const int ALLOWABLE_ATTEMPTS = 2;
}


enum MOVE {
	UP = 1,
	DOWN = -1,
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};



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
	bool improved(int current_max, std::vector<int>& neighbor);
	int get_max();


private:
	int config_size_;
	int least_fit_;


};


LocalSearch::LocalSearch(int size) :
	config_size_(size), least_fit_(size*(size - 1) / 2)
{}


LocalSearch::~LocalSearch() {

}


std::vector<int> LocalSearch::generate_config(int size) {
	std::mt19937 mt(static_cast<unsigned int>(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::vector<int> config(size);
	std::generate(config.begin(), config.end(),
		[&mt, size] { return mt() % size; });
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
				int neighbor_score = this->config_score(neighbor);
				if (neighbor_score >= current_max) {
					current = neighbor;
					current_max = neighbor_score;
				}
			}
		}
		attempts = this->improved(current_max, iteration) ? 0 : ++attempts;
	} while (attempts < ALLOWABLE_ATTEMPTS);
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


bool LocalSearch::improved(
	std::vector<int>& current,
	std::vector<int>& neighbor)
{
	return this->config_score(current) > this->config_score(neighbor);
}


bool LocalSearch::improved(int current_max, std::vector<int>& neighbor) {
	return current_max > this->config_score(neighbor);
}


int LocalSearch::get_max() {
	return least_fit_;
}



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
		if (this->goal_config(max_score, score))
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
		"The proportion of successes is " <<
		static_cast<double>(success) / total << "." << "\n" << std::endl;
	return 0;
}



int main(int argc, char* argv[]) {
	Core core;
	return core.run();
}

