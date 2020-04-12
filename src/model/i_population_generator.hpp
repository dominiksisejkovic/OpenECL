// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_POPULATION_GENERATOR_HPP
#define OPEN_ECL_I_POPULATION_GENERATOR_HPP

#include <memory>
#include <vector>
#include "solution/i_solution.hpp"
#include "i_population.hpp"

class IPopulationGenerator {
public:
    virtual ~IPopulationGenerator() {}

    virtual std::shared_ptr<IPopulation> execute() = 0;
};

#endif //OPEN_ECL_I_POPULATION_GENERATOR_HPP
