// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#include "algorithm_factory.hpp"
#include "operator_factory.hpp"
#include "population_generator_factory.hpp"

std::shared_ptr<IEvolutionaryAlgorithm> AlgorithmFactory::create(const std::string &algorithm_name) {
    std::shared_ptr<IEvolutionaryAlgorithm> algorithm;

    if (algorithm_name == "steady.state.genetic.algorithm" || algorithm_name == "generational.genetic.algorithm") {
        algorithm = this->createGeneticAlgorithm(algorithm_name);
    } else {
        throw std::runtime_error("Unsupported algorithm: " + algorithm_name);
    }

    return algorithm;
}

std::shared_ptr<GeneticAlgorithm> AlgorithmFactory::createGeneticAlgorithm(const std::string &ga_name) {
    // Get all necessary variable values
    auto selection_op_name = PropertyReader::getInstance().getEntry("operator.selection")->toString();
    auto crossover_op_name = PropertyReader::getInstance().getEntry("operator.crossover")->toString();
    auto mutation_op_name = PropertyReader::getInstance().getEntry("operator.mutation")->toString();
    auto replacement_op_name = PropertyReader::getInstance().getEntry("operator.replacement")->toString();
    auto solution_type = PropertyReader::getInstance().getEntry("solution.type")->toString();

    // Create operators
    auto selection = OperatorFactory::getInstance().createSelectionOperator(selection_op_name);
    auto crossover = OperatorFactory::getInstance().createCrossoverOperator(crossover_op_name);
    auto mutation = OperatorFactory::getInstance().createMutationOperator(mutation_op_name);
    auto replacement = OperatorFactory::getInstance().createReplacementOperator(replacement_op_name);
    auto population_generator = PopulationGeneratorFactory::getInstance().createGeneratorForSolutionTyp(solution_type);

    // Register components
    auto components_box = std::make_shared<ComponentsBox>();
    components_box->setSelection(selection);
    components_box->setCrossover(crossover);
    components_box->setMutation(mutation);
    components_box->setReplacement(replacement);
    components_box->setPopulationGenerator(population_generator);

    std::shared_ptr<GeneticAlgorithm> ga;
    if (ga_name == "steady.state.genetic.algorithm") {
        ga = std::make_shared<SteadyStateGeneticAlgorithm>(components_box);
    } else {
        ga = std::make_shared<GenerationalGeneticAlgorithm>(components_box);
    }

    return ga;
}

