#ifndef CORE_H_
#define CORE_H_
#include "evolution.h"


class Core {

public:
	Core();
	~Core();

	int run();


private:
	bool next_trial();
	inline bool enough_configs(Population& fittest);
	
	int complete(bool success);



};



#endif // !CORE_H_
