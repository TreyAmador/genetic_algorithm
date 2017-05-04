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

	int complete(bool success);



};



#endif // !CORE_H_
