#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <queue>


namespace {
	const int NUM_GENES = 21;
	const int POP_SIZE = 100;
	const int DESIRED_CONFIGS = 5;
	const int SENTINEL = -1;
}


enum MOVE {
	UP = 1,
	DOWN = -1,
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};



namespace util {

	template <class T>
	void print_1d(
		std::vector<T>& vec,
		std::string sep = " ", std::string end = "\n")
	{
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << vec[i] << sep;
		std::cout << end;
	}

	template <class T>
	void clear_vec(std::vector<T>& vec) {
		vec.clear();
		vec.shrink_to_fit();
	}

}


struct Organism {
	std::vector<int> genome_;
	int fitness_;
};

typedef std::vector<Organism> Population;


bool organism_sort(Organism& a, Organism& b) {
	return a.fitness_ > b.fitness_;
}



struct Data {

public:
	void init_trial() {
		trial_init_ = this->get_time();
	}

	long long end_trial() {
		long long delta = this->delta_time(trial_init_);
		trial_deltas_.push_back(delta);
		return delta;
	}

	std::chrono::nanoseconds get_time() {
		return std::chrono::high_resolution_clock::now().time_since_epoch();
	}

	long long delta_time(std::chrono::nanoseconds init) {
		std::chrono::nanoseconds current = this->get_time();
		auto delta = (current - init).count();
		return delta;
	}

	long long mean() {
		long long sum = 0;
		for (size_t i = 0; i < trial_deltas_.size(); ++i)
			sum += trial_deltas_[i];
		return sum / static_cast<long long>(trial_deltas_.size());
	}

private:
	std::chrono::nanoseconds trial_init_;
	std::vector<long long> trial_deltas_;

};



class IO {


public:
	IO(const std::string& filepath);
	~IO();

	void user_prompt(int queens, int trials);
	void iteration(Population& fittest);
	void summary(long long mean, Population& fittest, int generations);
	void print_population(Population& fittest);

	int terminate(bool success);


private:
	std::fstream fs_;
	size_t fit_organisms_;


};


IO::IO(const std::string& filepath) :
	fit_organisms_(0)
{}


IO::~IO() {

}


void IO::user_prompt(int queens, int trials) {
	std::string any_key;
	std::cout <<
		"Welcome to the " << queens <<
		"-Queens problem solver, which will find " << trials <<
		" configurations using a genetic algorithm." << "\n" << std::endl;
}


void IO::iteration(Population& fittest) {
	if (fittest.size() > fit_organisms_)
		std::cout << "\n" << "You have " << ++fit_organisms_ <<
		" solved configurations" << std::endl;
	else
		std::cout << ".";
}


void IO::summary(long long mean, Population& fittest, int generations) {
	std::cout << "\n" <<
		"This required " << mean <<
		" milliseconds per trial on average." << "\n" <<
		"The average number of generations was " << generations <<
		" generations." << "\n\n" << std::endl;
	this->print_population(fittest);
}


int IO::terminate(bool success) {
	std::cout << "\n" <<
		"The simulation has terminated." << "\n" << std::endl;
	return success ? 1 : -1;
}


void IO::print_population(Population& fittest) {
	std::cout <<
		"The following configurations have no collisions: " << "\n" << std::endl;
	for (auto iter = fittest.begin(); iter != fittest.end(); ++iter) {
		for (size_t i = 0; i < iter->genome_.size(); ++i)
			std::cout << iter->genome_[i] << " ";
		std::cout << std::endl;
	}
}



class Evolution {

public:
	Evolution(int num_genes);
	~Evolution();

	Population produce(size_t pop_size);
	Population reproduce(Population& parental);

	void mutate(Population& population);
	void replenish(Population& parental, Population& filial, int size);

	bool has_fittest(Population& population);
	void save_fittest(Population& population, Population& fittest, int size);

	void print_population(Population& population);


private:
	Organism crossover(Organism& male, Organism& female);
	void crossover(
		Organism& parent_a,
		Organism& parent_b,
		Organism& offspring);
	void crossover(
		Organism& offspring,
		Organism& parent,
		int beg, int end);

	int fitness(Organism& organism);
	void collisions(
		std::vector<int>& organism, int& fitness,
		size_t col, int hrz);
	int least_fit(int genes);

	Organism generate_organism(int size);
	std::vector<int> generate_genome(int size);
	void cull(Population& population);

	inline int base_pair();
	inline void snp(int& bp);
	inline bool is_mutable();
	inline std::mt19937 mt19937_seeded();

	inline void sort_population(Population& population);
	void clear_population(Population& population);

private:
	const int genome_size_;
	std::mt19937 mutation_;
	int least_fit_;


};


Evolution::Evolution(int num_genes) :
	genome_size_(num_genes),
	least_fit_(this->least_fit(num_genes)),
	mutation_(this->mt19937_seeded())
{}


Evolution::~Evolution() {

}


Population Evolution::produce(size_t pop_size) {
	Population population;
	while (population.size() < pop_size)
		population.push_back(this->generate_organism(genome_size_));
	this->sort_population(population);
	return population;
}


Population Evolution::reproduce(Population& population) {
	Population filial;
	int heirarchy = population.size() / 10;
	for (int m = 0; m < heirarchy; ++m)
		for (size_t f = heirarchy; f < population.size() / 5; ++f)
			filial.push_back(this->crossover(population[m], population[f]));
	return filial;
}


void Evolution::mutate(Population& pop) {
	for (auto p = pop.begin(); p != pop.end(); ++p) {
		if (this->is_mutable())
			this->snp(p->genome_[this->base_pair()]);
		p->fitness_ = this->fitness(*p);
	}
}


void Evolution::replenish(Population& parental, Population& filial, int size) {
	this->clear_population(parental);
	parental.resize(size);
	this->sort_population(filial);
	this->cull(filial);
	int max = size / 2 > static_cast<int>(filial.size()) ?
		filial.size() : size / 2;
	for (int i = 0; i < max; ++i)
		parental[i] = filial[i];
	for (size_t i = max; i < parental.size(); ++i)
		parental[i] = this->generate_organism(genome_size_);
	this->clear_population(filial);
	this->sort_population(parental);
}


bool Evolution::has_fittest(Population& population) {
	return population[0].fitness_ == least_fit_;
}


void Evolution::save_fittest(Population& pop, Population& fittest, int size) {
	for (size_t i = 0; i < pop.size() && pop[i].fitness_ == least_fit_; ++i)
		fittest.push_back(pop[i]);
	this->clear_population(pop);
	pop = this->produce(size);
}


void Evolution::print_population(Population& pop) {
	for (auto iter = pop.begin(); iter != pop.end(); ++iter) {
		util::print_1d(iter->genome_, " ", " ");
		std::cout << ", fitness: " << iter->fitness_ << "\n";
	}
}


// private methods
Organism Evolution::crossover(Organism& male, Organism& female) {
	Organism offspring;
	offspring.genome_.resize(genome_size_);
	if (mutation_() % 2)
		this->crossover(male, female, offspring);
	else
		this->crossover(female, male, offspring);
	return offspring;
}


void Evolution::crossover(
	Organism& parent_a,
	Organism& parent_b,
	Organism& offspring)
{
	int bp = this->base_pair();
	this->crossover(parent_a, offspring, 0, bp);
	this->crossover(parent_b, offspring, bp, offspring.genome_.size());
}


void Evolution::crossover(
	Organism& parent,
	Organism& offspring,
	int beg, int end)
{
	std::copy(
		parent.genome_.begin() + beg,
		parent.genome_.begin() + end,
		offspring.genome_.begin() + beg);
}


int Evolution::fitness(Organism& organism) {
	int fit_scr = 0;
	for (size_t i = 0; i < organism.genome_.size(); ++i) {
		this->collisions(organism.genome_, fit_scr, i, MOVE::STILL);
		this->collisions(organism.genome_, fit_scr, i, MOVE::UP);
		this->collisions(organism.genome_, fit_scr, i, MOVE::DOWN);
	}
	return least_fit_ - fit_scr;
}


void Evolution::collisions(
	std::vector<int>& org, int& fit_scr,
	size_t column, int hrz)
{
	size_t col = column;
	int row = org[col];
	int extr = hrz == MOVE::UP ? genome_size_ : -1;
	while (col < org.size() && row != extr) {
		if (org[col] == row && col != column)
			++fit_scr;
		++col;
		row += hrz;
	}
}


// could also be genes * ( genes - 1 ) / 2
int Evolution::least_fit(int genes) {
	int fit = 0;
	for (int i = 1; i < genes; ++i)
		fit += i;
	return fit;
}


Organism Evolution::generate_organism(int size) {
	Organism organism;
	organism.genome_ = this->generate_genome(size);
	organism.fitness_ = this->fitness(organism);
	return organism;
}


std::vector<int> Evolution::generate_genome(int size) {
	std::mt19937 mt = this->mt19937_seeded();
	std::vector<int> organism(size);
	std::generate(organism.begin(), organism.end(),
		[&mt, size] { return mt() % size; });
	return organism;
}


void Evolution::cull(Population& population) {
	auto iter = population.begin();
	while (iter != population.end() - 1) {
		if (iter->genome_ == (iter + 1)->genome_)
			population.erase(iter + 1);
		else
			++iter;
	}
}


inline int Evolution::base_pair() {
	return mutation_() % genome_size_;
}


inline void Evolution::snp(int& bp) {
	bp = (mutation_() + bp) % genome_size_;
}


inline bool Evolution::is_mutable() {
	return mutation_() % 3 == 0;
}


inline std::mt19937 Evolution::mt19937_seeded() {
	std::mt19937 mt(static_cast<unsigned int>(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	return mt;
}


inline void Evolution::sort_population(Population& pop) {
	std::sort(pop.begin(), pop.end(), organism_sort);
}


void Evolution::clear_population(Population& population) {
	for (size_t i = 0; i < population.size(); ++i)
		util::clear_vec(population[i].genome_);
	util::clear_vec(population);
}



class Core {

public:
	Core();
	~Core();

	int run();


private:
	void begin_trial(IO& io, Data& data, int size, int trials);
	void end_trial(IO& io, Data& data, Population& population, int generations);

	bool next_trial();
	inline bool enough_configs(Population& fittest);


};


Core::Core() {

}


Core::~Core() {

}


int Core::run() {
	IO io("");
	Data data;
	Evolution evolution(NUM_GENES);
	int generations = 0;
	while (this->next_trial()) {
		this->begin_trial(io, data, NUM_GENES, DESIRED_CONFIGS);
		Population fittest;
		Population parental = evolution.produce(POP_SIZE);
		while (!this->enough_configs(fittest)) {
			Population filial = evolution.reproduce(parental);
			evolution.mutate(filial);
			evolution.replenish(parental, filial, POP_SIZE);
			if (evolution.has_fittest(parental))
				evolution.save_fittest(parental, fittest, POP_SIZE);
			io.iteration(fittest);
			++generations;
		}
		this->end_trial(io, data, fittest, generations);
	}
	return io.terminate(true);
}


void Core::begin_trial(IO& io, Data& data, int size, int trials) {
	io.user_prompt(size, trials);
	data.init_trial();
}


void Core::end_trial(
	IO& io, Data& data,
	Population& population,
	int generations)
{
	long long delta = data.end_trial();
	long long mean = (delta / 1000000) / DESIRED_CONFIGS;
	io.summary(mean, population, generations / DESIRED_CONFIGS);
}


bool Core::next_trial() {
	static int trials = 0;
	if (trials++ < 1)
		return true;
	else
		return false;
}


inline bool Core::enough_configs(Population& fittest) {
	return fittest.size() >= DESIRED_CONFIGS;
}



int main(int argc, char* argv[]) {
	Core core;
	core.run();
	return 0;
}
