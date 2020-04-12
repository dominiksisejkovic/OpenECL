// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_GENETIC_ALGORITHM_HPP
#define OPEN_ECL_GENETIC_ALGORITHM_HPP

#include "../../../model/model.hpp"
#include "../../../utils/property_reader.hpp"

class GeneticAlgorithm : public IEvolutionaryAlgorithm {
public:

    ~GeneticAlgorithm() {}

    GeneticAlgorithm(const std::shared_ptr<ComponentsBox> &components_box) {
        this->crossover_ = components_box->getCrossover();
        this->selection_ = components_box->getSelection();
        this->mutation_ = components_box->getMutation();
        this->replacement_ = components_box->getReplacement();
        this->population_generator_ = components_box->getPopulationGenerator();
        this->max_iterations_ = PropertyReader::getInstance().getEntry("variable.max.iterations")->toInteger();
        this->elitism_ = PropertyReader::getInstance().getEntry("elitism")->toBoolean();
    }

protected:
    std::shared_ptr<IPopulationGenerator> population_generator_;
    std::shared_ptr<IPopulation> population_;
    std::shared_ptr<ICrossover> crossover_;
    std::shared_ptr<ISelection> selection_;
    std::shared_ptr<IMutation> mutation_;
    std::shared_ptr<IReplacement> replacement_;

    // Termination variables
    int max_iterations_;
    bool elitism_;
};


#endif //OPEN_ECL_GENETIC_ALGORITHM_HPP
