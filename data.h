#ifndef DATA_H_
#define DATA_H_
#include <vector>
#include <chrono>


struct Data {

public:
	//Data() {
	//}
	//~Data() {	
	//}

	void init_iter() {
		iter_init_ = this->get_time();
	}

	long long end_iter() {
		long long delta = this->delta_time(iter_init_);
		iter_deltas_.push_back(delta);
		return delta;
	}

	void init_trial() {
		trial_init_ = this->get_time();
	}

	long long end_trial() {
		long long delta = this->delta_time(trial_init_);
		trial_deltas_.push_back(delta);
		return delta;
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

	long long mean() {
		long long sum = 0;
		for (size_t i = 0; i < trial_deltas_.size(); ++i)
			sum += trial_deltas_[i];
		return sum / static_cast<long long>(trial_deltas_.size());
	}

private:
	std::chrono::nanoseconds trial_init_;
	std::chrono::nanoseconds iter_init_;
	std::vector<long long> trial_deltas_;
	std::vector<long long> iter_deltas_;


};









//typedef std::pair<std::chrono::nanoseconds, std::chrono::nanoseconds> TimePair;
//typedef std::vector<TimePair> TrialTime;



/*

typedef std::vector<long long> TimePoint;


struct Data {


public:

	void init_trial() {
		curr_trial_ = this->get_time();
	}

	void end_trial() {
		auto delta = this->get_time() - curr_trial_;
		trial_time_.push_back(delta.count());
	}

	void init_iter() {
		curr_iter_ = this->get_time();
	}

	void end_iter() {
		auto delta = this->get_time() - curr_iter_;
		iter_time_.push_back(delta.count());
	}

	std::chrono::nanoseconds get_time() {
		return std::chrono::high_resolution_clock::now().time_since_epoch();
	}

	



private:
	std::chrono::nanoseconds curr_iter_;
	std::chrono::nanoseconds curr_trial_;
	TimePoint trial_time_;
	TimePoint iter_time_;

};

*/




#endif
