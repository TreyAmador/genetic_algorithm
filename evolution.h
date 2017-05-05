#ifndef EVOLUTION_H_
#define EVOLUTION_H_
#include <vector>
#include <string>
#include <random>
#include <queue>


struct Organism {
	std::vector<int> genome_;
	int fitness_;
	//int operator[](int i) {
	//	return genome_[i];
	//}
};


//class Comparator {
//public:
//	bool operator()(Organism& a, Organism& b) {
//		return a.fitness_ > b.fitness_;
//	}
//};


//class Sorter {
//public:
//	bool operator()(Organism& a, Organism& b) {
//		return a.fitness_ > b.fitness_;
//	}
//};


//typedef std::vector<int> Organism;
typedef std::vector<Organism> Population;
//typedef Population::iterator PopIter;


//typedef std::priority_queue<Organism, std::vector<Organism>, Comparator> Population;





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

	
	
	//Population produce(size_t size, int fit_scr);

	Population produce(size_t pop_size, int fit_thr);


	//void crossover(Population& population);
	//void mutate(Population& population,int mutations);
	
	//void fitness(
	//	Population& population,
	//	Population& fit_set);
	
	
	//int fitness(Population& population);
	int fitness(Organism& organism);

	//int fitness(Organism& organ);


	//int mean_fitness(Population& population);

	void sort_population(Population& population);


	Organism generate_organism(int size);


	std::vector<int> generate_genome(int size);

	std::mt19937 mt19937_seeded();


	//void cull(Population& population);


private:


	void collisions(
		std::vector<int>& organism, int& fitness,
		size_t col, int hrz);
	int least_fit(int genes);

	int base_pair();
	void snp(int& bp);
	
	void clear_genes();


private:
	std::vector<int> genome_;
	const int genome_size_;
	std::mt19937 mutation_;

	int least_fit_;


};


#endif
