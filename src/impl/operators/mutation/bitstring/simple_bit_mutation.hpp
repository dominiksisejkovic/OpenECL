// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_SIMPLE_BIT_MUTATION_HPP
#define OPEN_ECL_SIMPLE_BIT_MUTATION_HPP

#include <random_utils.hpp>
#include "solutions/vector_based/bit_string_solution.hpp"

class SimpleBitMutation : public IMutation {
public:
    ~SimpleBitMutation() {}

    SimpleBitMutation(double mutation_probability)
            : mutation_probability_(mutation_probability) {}

    void execute(std::shared_ptr<ISolution> &solution) override {
        auto bitstring = std::dynamic_pointer_cast<BitStringSolution>(solution);
        for (int i = 0; i < bitstring->getSize(); ++i) {
            double rnd_probability = RandomUtils::getInstance().randomDouble();

            if (rnd_probability < this->mutation_probability_) {
                bitstring->flipOnIndex(i);
            }
        }
    }

protected:
    double mutation_probability_;
};

#endif //OPEN_ECL_SIMPLE_BIT_MUTATION_HPP
