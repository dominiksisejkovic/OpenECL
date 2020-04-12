// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_CROSSOVER_HPP
#define OPEN_ECL_I_CROSSOVER_HPP

#include "../solution/i_solution.hpp"
#include <vector>
#include <memory>

class ICrossover {
public:
    virtual ~ICrossover() {}

    virtual std::vector<std::shared_ptr<ISolution>>
    execute(std::vector<std::shared_ptr<ISolution>> &parents) = 0;
};

#endif //OPEN_ECL_I_CROSSOVER_HPP
