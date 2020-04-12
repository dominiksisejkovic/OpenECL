// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_ONE_MAX_FITNESS_EVALUATOR_HPP
#define OPEN_ECL_ONE_MAX_FITNESS_EVALUATOR_HPP

#include "../../model/i_fitness_evaluator.hpp"
#include "../solutions/vector_based/bit_string_solution.hpp"

class OneMaxFitnessEvaluator : public IFitnessEvaluator {
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

        auto fitness = bitstring->getFitness();
        fitness->setValue(num_ones);
    }
};

#endif //OPEN_ECL_ONE_MAX_FITNESS_EVALUATOR_HPP
