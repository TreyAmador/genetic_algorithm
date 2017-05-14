#ifndef CORE_H_
#define CORE_H_
#include <algorithm>
#include <chrono>
#include <vector>
#include "evolution.h"
struct Data;


class Core {

public:
	Core();
	~Core();

	int run();


private:
	bool next_trial();
	//std::chrono::nanoseconds get_time();
	//long long delta_time(std::chrono::nanoseconds init);
	inline bool enough_configs(Population& fittest);
	

};



#endif



/*

#ifndef DATA_H_
#define DATA_H_


struct Data {


public:
	Data() {

	}
	~Data() {

	}

	void init_iter() {
		iter_init_ = this->get_time();
	}
	void end_iter() {
		iter_deltas_.push_back(this->delta_time(iter_init_));
	}

	void init_trial() {
		trial_init_ = this->get_time();
	}
	void end_trial() {
		trial_deltas_.push_back(this->delta_time(trial_init_));
	}
	std::chrono::nanoseconds get_time() {
		return std::chrono::high_resolution_clock::now().time_since_epoch();
	}
	long long delta_time(std::chrono::nanoseconds init) {
		std::chrono::nanoseconds current = this->get_time();
		auto delta = (current - init).count();
		return delta;
	}
	void stats() {

	}
	long long mean(std::vector<long long>& delta) {
		long long sum = 0;
		for (size_t i = 0; i < delta.size(); ++i)
			sum += delta[i];
		return sum / static_cast<long long>(delta.size());
	}


private:
	std::chrono::nanoseconds trial_init_;
	std::chrono::nanoseconds iter_init_;
	std::vector<long long> trial_deltas_;
	std::vector<long long> iter_deltas_;

};


#endif

*/