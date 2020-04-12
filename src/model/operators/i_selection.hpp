// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_SELECTION_HPP
#define OPEN_ECL_I_SELECTION_HPP

#include <memory>
#include <vector>
#include "../solution/i_solution.hpp"
#include "../i_population.hpp"

class ISelection {
public:
    virtual ~ISelection() {}

    virtual std::vector<std::shared_ptr<ISolution>> execute(const std::shared_ptr<IPopulation> &population) = 0;
};


#endif //OPEN_ECL_I_SELECTION_HPP
