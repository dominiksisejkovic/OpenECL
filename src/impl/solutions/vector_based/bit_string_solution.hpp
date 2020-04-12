// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_BIT_STRING_SOLUTION_HPP
#define OPEN_ECL_BIT_STRING_SOLUTION_HPP

#include "../vector_based_solution.hpp"

class BitStringSolution : public VectorBasedSolution<bool> {
public:
    ~BitStringSolution() {}

    BitStringSolution(int size) : VectorBasedSolution(size) {}

    BitStringSolution(const std::vector<bool> &data) : VectorBasedSolution(data) {}

    const std::string toString() override {
        auto solution_string = std::string("[");

        auto data_size = getSize();
        for (int i = 0; i < data_size; ++i) {
            solution_string += data_[i] ? "1" : "0";

            if (i < data_size - 1) {
                solution_string += ", ";
            }
        }

        solution_string += "]";

        auto fitness_value = ISolution::getFitness()->getValue();
        return "{ " + std::to_string(fitness_value) + ", " + solution_string + " }";
    }
};


#endif //OPEN_ECL_BIT_STRING_SOLUTION_HPP
