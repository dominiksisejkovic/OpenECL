// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_FITNESS_EVALUATOR_HPP
#define OPEN_ECL_I_FITNESS_EVALUATOR_HPP

#include <memory>
#include <vector>
#include "solution/i_solution.hpp"
#include "i_population.hpp"

class IFitnessEvaluator {
public:
    virtual ~IFitnessEvaluator() {}

    virtual void evaluate(const std::shared_ptr<ISolution> &solution) = 0;

    virtual void evaluate(const std::shared_ptr<IPopulation> &population) {
        for (auto &solution: population->getSolutions()) {
            this->evaluate(solution);
        }
    }

    virtual void evaluate(const std::vector<std::shared_ptr<ISolution>> &solutions) {
        for (auto &solution: solutions) {
            this->evaluate(solution);
        }
    }
};

#endif //OPEN_ECL_I_FITNESS_EVALUATOR_HPP
