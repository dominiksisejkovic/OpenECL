// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_ALGORITHM_FACTORY_HPP
#define OPEN_ECL_ALGORITHM_FACTORY_HPP

#include <memory>
#include "../model/i_evolutionary_algorithm.hpp"
#include "../impl/algorithms.hpp"

/**
 * Singleton class responsible for creating instances of evolutionary algorithms.
 */
class AlgorithmFactory {
public:
    static AlgorithmFactory &getInstance() {
        static AlgorithmFactory instance_;
        return instance_;
    }

    /**
     * Creates an evolutionary algorithm of the given type.
     * @param algorithm_name Name of algorithm to be created.
     * @return Algorithm instance.
     */
    std::shared_ptr<IEvolutionaryAlgorithm> create(const std::string &algorithm_name);

private:
    std::shared_ptr<GeneticAlgorithm> createGeneticAlgorithm(const std::string &ga_name);

protected:
    ~AlgorithmFactory() {}

    AlgorithmFactory() {}

    // delete copy and move constructors and assign operators
    AlgorithmFactory(AlgorithmFactory const &) = delete;             // Copy construct
    AlgorithmFactory(AlgorithmFactory &&) = delete;                  // Move construct
    AlgorithmFactory &operator=(AlgorithmFactory const &) = delete;  // Copy assign
    AlgorithmFactory &operator=(AlgorithmFactory &&) = delete;      // Move assign

    static AlgorithmFactory *instance_;
};


#endif //OPEN_ECL_ALGORITHM_FACTORY_HPP
