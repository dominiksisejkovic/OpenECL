// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_POPULATION_GENERATOR_FACTORY_HPP
#define OPEN_ECL_POPULATION_GENERATOR_FACTORY_HPP

#include "../model/i_population_generator.hpp"
#include "../impl/population_generators.hpp"
#include <string>
#include <memory>

/**
 * Singleton class responsible for creating populations of selected types.
 */
class PopulationGeneratorFactory {
public:
    static PopulationGeneratorFactory &getInstance() {
        static PopulationGeneratorFactory instance_;
        return instance_;
    }

    /**
     * Creates an instance of a population generator for the given type
     * @param solution_type Solution type name.
     * @return Population generator instance.
     */
    std::shared_ptr<IPopulationGenerator> createGeneratorForSolutionTyp(const std::string &solution_type);

protected:
    ~PopulationGeneratorFactory() {}

    PopulationGeneratorFactory() {}

    // delete copy and move constructors and assign operators
    PopulationGeneratorFactory(PopulationGeneratorFactory const &) = delete;             // Copy construct
    PopulationGeneratorFactory(PopulationGeneratorFactory &&) = delete;                  // Move construct
    PopulationGeneratorFactory &operator=(PopulationGeneratorFactory const &) = delete;  // Copy assign
    PopulationGeneratorFactory &operator=(PopulationGeneratorFactory &&) = delete;       // Move assign

    static PopulationGeneratorFactory *instance_;
};


#endif //OPEN_ECL_POPULATION_GENERATOR_FACTORY_HPP
