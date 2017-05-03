#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>
#include <random>

typedef std::vector<std::vector<int> > Population;
typedef std::vector<int> Gene;


class Evolution {


public:
	Evolution(int num_genes);
	~Evolution();

	Population reproduce(int size);
	void crossover(Population& population);
	void mutate(Population& population,int mutations);
	
	int fitness(Population& population);

	
private:
	int base_pair();
	void snp(int& bp);
	
	void clear_genes();


private:
	Gene genome_;
	const int genome_size_;
	std::mt19937 mutation_;


};


#endif
