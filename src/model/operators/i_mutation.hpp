// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_MUTATION_HPP
#define OPEN_ECL_I_MUTATION_HPP

#include <memory>
#include <vector>
#include "../solution/i_solution.hpp"

class IMutation {
public:
    virtual ~IMutation() {}

    virtual void execute(std::shared_ptr<ISolution> &solution) = 0;

    virtual void execute(std::vector<std::shared_ptr<ISolution>> &solutions) {
        for (auto &solution: solutions) {
            this->execute(solution);
        }
    }
};


#endif //OPEN_ECL_I_MUTATION_HPP
