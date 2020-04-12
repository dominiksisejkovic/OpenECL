// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_N_WORST_REPLACEMENT_HPP
#define OPEN_ECL_N_WORST_REPLACEMENT_HPP

#include "../../model/operators/i_replacement.hpp"

class NWorstReplacement : public IReplacement {
public:
    ~NWorstReplacement() {}

    NWorstReplacement() {}

    void execute(const std::shared_ptr<IPopulation> &population,
                 const std::vector<std::shared_ptr<ISolution>> &new_solutions) override {
        auto population_solutions = population->getSolutions();

        std::sort(
                population_solutions.begin(),
                population_solutions.end(),
                [](const std::shared_ptr<ISolution> &first, const std::shared_ptr<ISolution> &second) {
                    return first->isWorseThan(second);
                }
        );

        auto new_solution_size = static_cast<int>(new_solutions.size());
        for (int i = 0; i < new_solution_size; ++i) {
            population->replaceSolution(
                    population_solutions[i], // Old
                    new_solutions[i]         // New
            );
        }
    }
};

#endif //OPEN_ECL_N_WORST_REPLACEMENT_HPP
