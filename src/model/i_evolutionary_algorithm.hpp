// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_EVOLUTIONARY_ALGORITHM_HPP
#define OPEN_ECL_I_EVOLUTIONARY_ALGORITHM_HPP

#include <memory>
#include <vector>
#include "solution/i_solution.hpp"
#include "i_fitness_evaluator.hpp"
#include <iostream>

class IEvolutionaryAlgorithm {
public:
    virtual ~IEvolutionaryAlgorithm() {}

    virtual std::shared_ptr<IPopulation> execute(const std::shared_ptr<IFitnessEvaluator> &fitness_evaluator) = 0;

    virtual void log(int iteration, const std::shared_ptr<IPopulation> &population) const {
        auto best = population->getBestSolution();
        std::cout << "| Iteration: " << iteration << std::endl;
        std::cout << "\t| Best fitness: " << best->getFitness()->getValue() << std::endl;
    }
};

#endif //OPEN_ECL_I_EVOLUTIONARY_ALGORITHM_HPP
