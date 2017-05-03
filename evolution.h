#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>


class Evolution {


public:
	Evolution(int num_genes);
	~Evolution();

	std::vector<std::vector<int> > reproduce(int size);

	void cross_population(
		std::vector<std::vector<int> >& population, 
		int crosses, int magnitude);

	void crossover(std::vector<int>& x, std::vector<int>& y, int magnitude);
	void mutate(std::vector<int>& organism, int mutations);


private:
	void clear_genes();


private:
	std::vector<int> genome_;
	const int genome_size_;


};


#endif
