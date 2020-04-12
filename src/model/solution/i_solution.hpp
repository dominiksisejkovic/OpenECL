// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)
#ifndef OPEN_ECL_I_SOLUTION_HPP
#define OPEN_ECL_I_SOLUTION_HPP

#include <memory>
#include <utility>
#include "../../utils/property_reader.hpp"
#include "i_fitness.hpp"

class ISolution {
public:
    virtual ~ISolution() {}

    ISolution() {
        auto fitness_objective_entry = PropertyReader::getInstance().getEntry("fitness.objective");
        auto fitness_objective = fitness_objective_entry->toString() == "min" ? FitnessObjective::MIN
                                                                              : FitnessObjective::MAX;
        this->fitness_ = std::make_shared<IFitness>(fitness_objective);
    }

    virtual std::shared_ptr<IFitness> getFitness() {
        return this->fitness_;
    };

    virtual void setFitness(std::shared_ptr<IFitness> fitness) {
        this->fitness_ = std::move(fitness);
    }

    virtual bool isBetterThan(const std::shared_ptr<ISolution> &other) {
        return this->fitness_->isBetterThan(other->getFitness());
    }

    virtual bool isWorseThan(const std::shared_ptr<ISolution> &other) {
        return this->fitness_->isWorseThan(other->getFitness());
    }

    virtual const std::string toString() = 0;

protected:
    std::shared_ptr<IFitness> fitness_;
};

#endif //OPEN_ECL_I_SOLUTION_HPP
