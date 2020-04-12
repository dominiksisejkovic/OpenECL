// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_TWO_POINT_CROSSOVER_HPP
#define OPEN_ECL_TWO_POINT_CROSSOVER_HPP

#include "../../../../utils/random_utils.hpp"
#include "../../../../model/operators/i_crossover.hpp"
#include "solutions/vector_based/bit_string_solution.hpp"

class TwoPointCrossover : public ICrossover {
public:
    ~TwoPointCrossover() {}

    std::vector<std::shared_ptr<ISolution>> execute(std::vector<std::shared_ptr<ISolution>> &parents) override {
        if (parents.size() != 2) {
            throw std::runtime_error("NPointCrossover expects exactly 2 parent solutions");
        }

        // Get parents
        auto parent_1 = std::dynamic_pointer_cast<BitStringSolution>(parents[0]);
        auto parent_2 = std::dynamic_pointer_cast<BitStringSolution>(parents[1]);
        auto solution_size = parent_1->getSize();

        // Prepare children
        auto child_1 = std::make_shared<BitStringSolution>(solution_size);
        auto child_2 = std::make_shared<BitStringSolution>(solution_size);

        // Get two unique indexes
        auto indexes = RandomUtils::getInstance().getNUniqueIntegersInRange(2, 0, solution_size - 1, true);

        // Copy parent genes
        for (int i = 0; i < indexes[0]; i++) {
            child_1->setValueOnIndex(i, parent_1->getValueOnIndex(i));
            child_2->setValueOnIndex(i, parent_2->getValueOnIndex(i));
        }

        for (int i = indexes[0]; i < indexes[1]; i++) {
            child_1->setValueOnIndex(i, parent_2->getValueOnIndex(i));
            child_2->setValueOnIndex(i, parent_1->getValueOnIndex(i));
        }

        for (int i = indexes[1]; i < solution_size; i++) {
            child_1->setValueOnIndex(i, parent_1->getValueOnIndex(i));
            child_2->setValueOnIndex(i, parent_2->getValueOnIndex(i));
        }

        return {child_1, child_2};
    }
};

#endif //OPEN_ECL_TWO_POINT_CROSSOVER_HPP
