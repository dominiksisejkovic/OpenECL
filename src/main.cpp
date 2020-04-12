#include "lib/open_ecl.hpp"    // Load the OpenECL library
#include "impl/optimization_problem/one_max_fitness_evaluator.hpp"  // Load your optimization problem

// Add your code here
void setupAndExecute() {
    // Get selected algorithm type
    auto algorithm_type = PropertyReader::getInstance().getEntry("evo.alg")->toString();

    // Create optimization problem, i.e., fitness evaluator
    std::shared_ptr<IFitnessEvaluator> one_max_evaluator = std::make_shared<OneMaxFitnessEvaluator>();

    // Create algorithm instance
    auto ga = AlgorithmFactory::getInstance().create(algorithm_type);

    // Execute algorithm on the given optimization problem
    auto population = ga->execute(one_max_evaluator);

    // Retrieve the best solutions from the final population
    auto best = population->getBestSolution();
    std::cout << best->toString() << std::endl;
}


int main(int argc, char *argv[]) {
    try {
        // Load properties: if successful -> setup and execute algorithm
        if (loadProperties(argc, argv)) {
            setupAndExecute();
        }
    } catch (const std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}


