// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_REPLACEMENT_HPP
#define OPEN_ECL_I_REPLACEMENT_HPP

#include "../i_population.hpp"

class IReplacement {
public:
    virtual ~IReplacement() {}

    virtual void
    execute(const std::shared_ptr<IPopulation> &population,
            const std::vector<std::shared_ptr<ISolution>> &new_solutions) = 0;
};

#endif //OPEN_ECL_I_REPLACEMENT_HPP
