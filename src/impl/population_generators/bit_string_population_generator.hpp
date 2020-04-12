// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_BIT_STRING_POPULATION_GENERATOR_HPP
#define OPEN_ECL_BIT_STRING_POPULATION_GENERATOR_HPP

#include "../../model/i_population_generator.hpp"
#include "../solutions/vector_based/bit_string_solution.hpp"
#include "../../utils/random_utils.hpp"
#include "../../utils/property_reader.hpp"

class BitStringPopulationGenerator : public IPopulationGenerator {
public:
    ~BitStringPopulationGenerator() {}

    BitStringPopulationGenerator() {
        this->size_ = PropertyReader::getInstance().getEntry("population.size")->toInteger();
        if (this->size_ < 3) {
            throw std::runtime_error("BitStringPopulationGenerator: population must have at least 2 solutions");
        }

        this->solution_size_ = PropertyReader::getInstance().getEntry("bit.string.size")->toInteger();
        if (this->solution_size_ < 1) {
            throw std::runtime_error("BitStringPopulationGenerator: solutions size must be greater than 0.");
        }
    }

    std::shared_ptr<IPopulation> execute() override {
        std::shared_ptr<IPopulation> population = std::make_shared<IPopulation>();

        for (int i = 0; i < this->size_; ++i) {
            auto chromosome = RandomUtils::getInstance().randomBoolVector(this->solution_size_);
            auto bitstring = std::make_shared<BitStringSolution>(chromosome);
            population->registerSolution(bitstring);
        }

        return population;
    }

protected:
    int size_;  // size of the population
    int solution_size_;
};

#endif //OPEN_ECL_BIT_STRING_POPULATION_GENERATOR_HPP
