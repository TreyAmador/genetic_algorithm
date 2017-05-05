#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>
#include <random>
#include <queue>


enum MOVE {
	UP = 1,
	DOWN = -1,
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};


struct Organism {
	std::vector<int> genome_;
	int fitness_;
};


typedef std::vector<Organism> Population;


class Evolution {

public:
	Evolution(int num_genes);
	~Evolution();

	Population produce(size_t pop_size, int fit_thr);
	Population reproduce(Population& parental);

	Organism crossover(Organism& male, Organism& female);
	void crossover(
		Organism& parent_a,
		Organism& parent_b,
		Organism& offspring);
	void crossover(
		Organism& offspring,
		Organism& parent,
		int beg, int end);

	void mutate(Population& population);	
	void cull(Population& population, int threshold);
	
	
	int fitness(Organism& organism);

	Organism generate_organism(int size);
	std::vector<int> generate_genome(int size);

	inline void sort_population(Population& population);
	inline std::mt19937 mt19937_seeded();


	void print_population(Population& population);


private:
	void collisions(
		std::vector<int>& organism, int& fitness,
		size_t col, int hrz);
	int least_fit(int genes);

	inline int base_pair();
	inline void snp(int& bp);
	
	
private:
	const int genome_size_;
	std::mt19937 mutation_;

	int least_fit_;


};


#endif
