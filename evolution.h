#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>
#include <random>

typedef std::vector<int> Organism;
typedef std::vector<Organism> Population;


enum MOVE {
	UP = 1,
	DOWN = -1,
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};


class Evolution {


public:
	Evolution(int num_genes);
	~Evolution();

	int fitness(Population& population);

	Population reproduce(int size);
	void crossover(Population& population);
	void mutate(Population& population,int mutations);
	
	// move to private
	int fitness(Organism& organism);
	void collisions(
		Organism& organism, int& fitness,
		size_t col, int hrz);



private:
	
	void each_collision(
		Organism& organism, int& fitness,
		size_t col, int hrz);

	int base_pair();
	void snp(int& bp);
	
	void clear_genes();


private:
	Organism genome_;
	const int genome_size_;
	std::mt19937 mutation_;

	int max_fitness_;


};


#endif
