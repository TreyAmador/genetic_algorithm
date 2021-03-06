#ifndef CORE_H_
#define CORE_H_
#include "evolution.h"
#include "data.h"
#include "io.h"


class Core {

public:
	Core();
	~Core();

	int run();


private:
	void begin_trial(IO& io, Data& data, int size, int trials);
	void end_trial(IO& io, Data& data, Population& population, int generations);

	bool next_trial();
	inline bool enough_configs(Population& fittest);
	

};


#endif // !CORE_H_
