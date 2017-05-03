#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>



class Evolution {


public:
	Evolution(int num_genes);
	~Evolution();

	std::vector<std::vector<int> > reproduce(int size);
	void crossover(std::vector<int>& x, std::vector<int>& y, int crosses);
	void mutate(std::vector<int>& organism, int mutations);


private:
	void clear_genes();


private:
	std::vector<int> genome_;
	const int genome_size_;


};


#endif
