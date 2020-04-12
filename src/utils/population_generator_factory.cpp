// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#include "population_generator_factory.hpp"
#include "../impl/population_generators.hpp"

std::shared_ptr<IPopulationGenerator>
PopulationGeneratorFactory::createGeneratorForSolutionTyp(const std::string &solution_type) {
    std::shared_ptr<IPopulationGenerator> population_generator;

    if (solution_type == "bit.string") {
        population_generator = std::make_shared<BitStringPopulationGenerator>();
    } else {
        throw std::runtime_error("Unsupported solutions operator: " + solution_type);
    }

    return population_generator;
}

