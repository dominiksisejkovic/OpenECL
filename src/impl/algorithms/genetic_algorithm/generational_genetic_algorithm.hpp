// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_GENERATIONAL_GENETIC_ALGORITHM_HPP
#define OPEN_ECL_GENERATIONAL_GENETIC_ALGORITHM_HPP

#include "genetic_algorithm.hpp"

class GenerationalGeneticAlgorithm : public GeneticAlgorithm {
public:

    ~GenerationalGeneticAlgorithm() {}

    GenerationalGeneticAlgorithm(const std::shared_ptr<ComponentsBox> &componentsBox)
            : GeneticAlgorithm(componentsBox) {}

    std::shared_ptr<IPopulation> execute(const std::shared_ptr<IFitnessEvaluator> &fitness_evaluator) override {
        population_ = population_generator_->execute();
        fitness_evaluator->evaluate(population_);

        for (int i = 0; i < this->max_iterations_; ++i) {
            auto next_generation = std::make_shared<IPopulation>();

            // Create next generation
            for (int j = 0; j < population_->getSize(); ++j) {
                auto parents = selection_->execute(population_);
                auto children = crossover_->execute(parents);

                mutation_->execute(children[0]);
                fitness_evaluator->evaluate(children[0]);
                next_generation->registerSolution(children[0]);
            }

            if (GeneticAlgorithm::elitism_) {
                // Preserve best solutions from previous generation
                auto best = population_->getBestSolution();
                next_generation->replaceWorstSolutionWith(best);
            }

            // Replace generation
            population_ = next_generation;

            log(i, population_);
        }

        return this->population_;
    }
};

#endif //OPEN_ECL_GENERATIONAL_GENETIC_ALGORITHM_HPP
