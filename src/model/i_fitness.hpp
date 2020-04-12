// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_FITNESS_HPP
#define OPEN_ECL_I_FITNESS_HPP

enum FitnessObjective {
    MIN, MAX
};

class IFitness {
public:
    ~IFitness() {}

    IFitness(FitnessObjective fitness_objective) :
            IFitness(fitness_objective, 0.0) {}

    IFitness(FitnessObjective fitness_objective, float value) :
            fitness_objective_(fitness_objective), value_(value) {}

    virtual float getValue() const {
        return this->value_;
    }

    virtual void setValue(float value) {
        this->value_ = value;
    }

    FitnessObjective getFitnessObjective() const {
        return fitness_objective_;
    }

    bool isBetterThan(const std::shared_ptr<IFitness> &other_fitness) {
        if (fitness_objective_ == FitnessObjective::MIN) {
            return this->value_ < other_fitness->getValue();
        } else {
            return this->value_ > other_fitness->getValue();
        }
    }

    bool isWorseThan(const std::shared_ptr<IFitness> &other_fitness) {
        if (fitness_objective_ == FitnessObjective::MIN) {
            return this->value_ > other_fitness->getValue();
        } else {
            return this->value_ < other_fitness->getValue();
        }
    }


private:
    FitnessObjective fitness_objective_;
    float value_;
};

#endif //OPEN_ECL_I_FITNESS_HPP


