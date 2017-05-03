#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>
#include <random>


class Evolution {


public:
	Evolution(int num_genes);
	~Evolution();

	std::vector<std::vector<int> > reproduce(int size);

	void crossover(
		std::vector<std::vector<int> >& population, 
		int swaps, int crosses);
	

	void mutate(
		std::vector<std::vector<int> >& population,
		int mutations);
	

	int base_pair();
	void snp(int& bp);

	void clear_genes();

	
private:
	void crossover(
		std::vector<int>& male,
		std::vector<int>& female,
		int crosses);

	void mutate(std::vector<int>& organism, int mutations);


private:
	std::vector<int> genome_;
	const int genome_size_;
	std::mt19937 mutation_;


};


#endif
