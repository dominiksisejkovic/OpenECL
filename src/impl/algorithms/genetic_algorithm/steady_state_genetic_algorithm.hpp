// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_STEADY_STATE_GENETIC_ALGORITHM_HPP
#define OPEN_ECL_STEADY_STATE_GENETIC_ALGORITHM_HPP

#include "genetic_algorithm.hpp"

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

#endif //OPEN_ECL_STEADY_STATE_GENETIC_ALGORITHM_HPP
