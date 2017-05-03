#include "evolution.h"
#include "utilities.h"
#include "core.h"


namespace {
	const int NUM_GENES = 20;
}


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	
	Evolution evolution(NUM_GENES);
	while (this->next_trail()) {
		auto population = evolution.reproduce(100);
		while (this->unsolved()) {
			// cross over
			// mutate
		}
	}
	
	return 0;
}



bool Core::next_trail() {
	//return true;
	static int trials = 0;
	if (trials++ < 1)
		return true;
	else
		return false;
}


bool Core::unsolved() {
	//return true;
	return false;
}



