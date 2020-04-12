# OpenECL: The Free Evolutionary Computation Library in C++

This repository contains a C++ implementation of an evolutionary computation library that can be used as a **template** with the basic facilities to **create your own algorithm** to solve complex black-box optimization problems. The concept of the library is not to offer every kind of algorithm or genotpy, but rather to expose the very basics to easily get started on your own projects!

-> add reference here

## Table of Content
1. [Design Principles](#design-principles)
2. [Supported Features](#supported-features)
3. [Source Tree](#source-tree)
4. [Library Components](#library-components)
5. [Adding Components - Example](#adding-components)
6. [Configuration File](#config)
7. [Getting Started](#getting-started)


<a name="design-principles"></a>
## Design Principles
OpenECL is written to be simple, extensible and "safe" to use. Therefore, ECL is based on OOP and relies on using smart pointers. The whole code base has been analyzed with valgrind to rule out any potential memory leaks. The code itself is self-documenting and should be easy to uderstand. The code is modular and structurally devided. Therefore, it should be easy to understand all components of the library and add new implementations with minimal effort.

<a name="supported-features"></a>
## Supported Features
The basic features of ECL are summarized as follows:
* Evolutionary Algorithms:
    * Genetic Algorithms:
      * Generational GA
      * Steady State GA
* Genotypes:
   * Bitstring
* Operators:
   * Crossover:
      * Vector-based:
         * One-Point Crossover
         * Two-Point Crossover
   * Mutation:
        * Bitstring:
            * Simple Bit Mutation
   * Replacement:
      * N-Wort
   * Selection:
      * K-Tournament

<a name="source-tree"></a>
## Source Tree
```bash
src/
├── impl
│   ├── algorithms
│   │   └── genetic_algorithm
│   │       ├── generational_genetic_algorithm.hpp
│   │       ├── genetic_algorithm.hpp
│   │       └── steady_state_genetic_algorithm.hpp
│   ├── algorithms.hpp
│   ├── operators
│   │   ├── crossover
│   │   │   └── vector_based
│   │   │       ├── one_point_crossover.hpp
│   │   │       └── two_point_crossover.hpp
│   │   ├── crossover_operators.hpp
│   │   ├── mutation
│   │   │   └── bitstring
│   │   │       └── simple_bit_mutation.hpp
│   │   ├── mutation_operators.hpp
│   │   ├── replacement
│   │   │   └── n_worst_replacement.hpp
│   │   ├── replacement_operators.hpp
│   │   ├── selection
│   │   │   └── k_tournament_selection.hpp
│   │   └── selection_operators.hpp
│   ├── operators.hpp
│   ├── optimization_problem
│   │   └── one_max_fitness_evaluator.hpp
│   ├── population_generators
│   │   └── bit_string_population_generator.hpp
│   ├── population_generators.hpp
│   ├── solutions
│   │   ├── vector_based
│   │   │   └── bit_string_solution.hpp
│   │   └── vector_based_solution.hpp
│   └── solutions.hpp
├── lib
│   └── open_ecl.hpp
├── main.cpp
├── model
│   ├── components_box.hpp
│   ├── i_evolutionary_algorithm.hpp
│   ├── i_fitness_evaluator.hpp
│   ├── i_fitness.hpp
│   ├── i_population_generator.hpp
│   ├── i_population.hpp
│   ├── model.hpp
│   ├── operators
│   │   ├── i_crossover.hpp
│   │   ├── i_mutation.hpp
│   │   ├── i_replacement.hpp
│   │   ├── i_selection.hpp
│   │   └── operators_model.hpp
│   └── solution
│       └── i_solution.hpp
└── utils
    ├── algorithm_factory.cpp
    ├── algorithm_factory.hpp
    ├── data_utils.hpp
    ├── operator_factory.hpp
    ├── population_generator_factory.cpp
    ├── population_generator_factory.hpp
    ├── property_entry.hpp
    ├── property_reader.hpp
    └── random_utils.hpp
```
<a name="library-components"></a>
## Library Components
The library includes the following interfaces (see src/model/):

* IEvolutionaryAlgorithm: Represents the evolutionary algorithm.
* ISolution: Represents a solution (genotype).
* IFitness: Represents the fitness. Can be configures as MAX or MIN. Every solution has a reference to its own fitness object.
* IFitnessEvaluator: Represents the actual optimization problem, i.e., the "evaluator of the fitness".
* IPopulation: Represents a complete population of solutions.
* IPopulationGenerator: Represents a class that is responsible for the (initial) generation of a population.
* ICrossover: Represents the crossover operator class.
* IMutation: Represents the mutation operator class.
* ISelection: Represents the selection operator class.
* IReplacement: Represents the replacement operator class (defines how solutions are replaces in a population).
* ComponentBox: Represents a set of all registered components. A single ComponentBox object is used to 

<a name="adding-components"></a>
## Adding Components - Examples
In the following, you can find some examples of how to add new components based on the mentioned interfaces (I am reusing the already implemented components as template).

### Mutation Operator
```cpp
class SimpleBitMutation : public IMutation { // Extend the IMutation class and override 'execute'
public:
    ~SimpleBitMutation() {}

    SimpleBitMutation(double mutation_probability)
            : mutation_probability_(mutation_probability) {}

    void execute(std::shared_ptr<ISolution> &solution) override {
        auto bitstring = std::dynamic_pointer_cast<BitStringSolution>(solution);
        for (int i = 0; i < bitstring->getSize(); ++i) {
            double rnd_probability = RandomUtils::getInstance().randomDouble();

            if (rnd_probability < this->mutation_probability_) {
                bitstring->flipOnIndex(i);
            }
        }
    }

protected:
    double mutation_probability_;
};
``` 
In the above example, the SimpleBitMutation extends the IMutation interface and overrides the mandatory 'execute' function. The function receives a single ISolution pointer and performs the selected mutation. Note that the derived class must be aware of the exact solution type (genotype). In this case, the SimpleBitMutation has a specific 'mutation_probability' argument that needs to be provided in the constructor. This probability can be given in the properties file and read during the setup. Simmilarly, all other interfaces can be simply extended by using the provided infrastructure.

### Fitness Evaluator (new optimization problem)
```cpp

class OneMaxFitnessEvaluator : public IFitnessEvaluator {   // Extend IFitnessEvaluator class and override the 'evaluate' function
public:
    ~OneMaxFitnessEvaluator() {}

    OneMaxFitnessEvaluator() {}

    void evaluate(const std::shared_ptr<ISolution> &solution) override {
        auto bitstring = std::dynamic_pointer_cast<BitStringSolution>(solution);

        float num_ones = 0;
        for (int i = 0; i < bitstring->getSize(); ++i) {
            if (bitstring->getValueOnIndex(i)) {
                ++num_ones;
            }
        }

        auto fitness = bitstring->getFitness();  // get reference to the fitness object of the solution
        fitness->setValue(num_ones);  // set the fitness value
    }
};
```
To add a new optimization problem, simply override the IFitnessEvaluator. The idea is very simple: the fitness evaluator evaluates the fitness of a single or multiple solutions (the execute function a multiple solutions is implemented in the IFitnessEvaluator class).

### Steady State Genetic Algorithm
```cpp

class SteadyStateGeneticAlgorithm : public GeneticAlgorithm {
public:

    ~SteadyStateGeneticAlgorithm() {}

    SteadyStateGeneticAlgorithm(const std::shared_ptr<ComponentsBox> &componentsBox)
            : GeneticAlgorithm(componentsBox) {}

    std::shared_ptr<IPopulation> execute(const std::shared_ptr<IFitnessEvaluator> &fitness_evaluator) override {
        population_ = population_generator_->execute();
        fitness_evaluator->evaluate(population_);

        for (int i = 0; i < this->max_iterations_; ++i) {
            auto parents = selection_->execute(population_);
            auto children = crossover_->execute(parents);

            for (auto &child: children) {
                mutation_->execute(child);
            }

            fitness_evaluator->evaluate(children);
            replacement_->execute(population_, children);

            log(i, population_);
        }

        return this->population_;
    }
};
```

<a name="config"></a>
## Configuration File
When implementing new components, you can add the specific configuration parameters to the 'evo.properties' file which will be loaded on startup:
```
## Setup algorithm 
# [steady.state.genetic.algorithm, generational.genetic.algorithm]
evo.alg=steady.state.genetic.algorithm

# [max, min]
fitness.objective=max
solution.type=bit.string
population.size=150
bit.string.size=50
variable.max.iterations=100

# [true, false]
elitism=true

## Setup mutation operator
operator.mutation=simple.bit
operator.mutation.simple.bit.probability=0.1

## Setup crossover operator
# [one.point, two.point]
operator.crossover=two.point

## Setup replacement operator
operator.replacement=n.worst

## Setup selection operator
operator.selection=k.tournament
operator.selection.k.tournament.size=3
operator.selection.k.tournament.num.parents=2
```
<a name="design-principles"></a>
## Getting Started
Once you download all your files, you can include them in your project or use the available 'main.cpp'. See the following for details.
```cpp
#include "lib/open_ecl.hpp"    // Load the OpenECL library
#include "impl/optimization_problem/one_max_fitness_evaluator.hpp"  // Load your optimization problem

// Add your code here
void setupAndExecute() {
    // Get selected algorithm type
    auto algorithm_type = PropertyReader::getInstance().getEntry("evo.alg")->toString();

    // Create optimization problem, i.e., fitness evaluator
    std::shared_ptr<IFitnessEvaluator> one_max_evaluator = std::make_shared<OneMaxFitnessEvaluator>();

    // Create algorithm instance
    auto ga = AlgorithmFactory::getInstance().create(algorithm_type);

    // Execute algorithm on the given optimization problem
    auto population = ga->execute(one_max_evaluator);

    // Retrieve the best solutions from the final population
    auto best = population->getBestSolution();
    std::cout << best->toString() << std::endl;
}


int main(int argc, char *argv[]) {
    try {
        // Load properties: if successful -> setup and execute algorithm
        if (loadProperties(argc, argv)) {
            setupAndExecute();
        }
    } catch (const std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
```

To run the programme, just add the config file as the first argument: ./OpenECL "../evo.properties""