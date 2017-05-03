#ifndef CORE_H_
#define CORE_H_


class Core {

public:
	Core();
	~Core();

	int run();


private:
	bool next_trail();
	bool unsolved();



};



#endif // !CORE_H_
