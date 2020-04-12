// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef ECL_VECTOR_BASED_SOLUTION_HPP
#define ECL_VECTOR_BASED_SOLUTION_HPP

#include "../../model/solution/i_solution.hpp"
#include <vector>

template<typename T>
class VectorBasedSolution : public ISolution {
public:
    ~VectorBasedSolution() {}

    VectorBasedSolution(int size) : data_(size) {}

    VectorBasedSolution(const std::vector<T> &data) : data_(data) {}

    bool getValueOnIndex(int index) const {
        if (index < 0 || index > getSize() - 1) {
            throw std::runtime_error("VectorBasedSolution: index out of scope.");
        }

        return data_[index];
    }

    void setValueOnIndex(int index, T value) {
        if (index < 0 || index > getSize() - 1) {
            throw std::runtime_error("VectorBasedSolution: index out of scope.");
        }

        data_[index] = value;
    }

    void flipOnIndex(int index) {
        if (index < 0 || index > getSize() - 1) {
            throw std::runtime_error("VectorBasedSolution: index out of scope.");
        }

        data_[index] = !data_[index];
    }

    int getSize() const {
        return data_.size();
    }

    void setData(const std::vector<T> &data) {
        data_ = data;
    }

    int getSize() {
        return static_cast<int>(data_.size());
    }

    const std::string toString() override {
        auto solution_string = std::string("[");

        auto data_size = getSize();
        for (int i = 0; i < data_size; ++i) {
            solution_string += data_[i];

            if (i < data_size - 1) {
                solution_string += ", ";
            }
        }

        solution_string += "]";

        auto fitness_value = ISolution::getFitness()->getValue();
        return "{ " + std::to_string(fitness_value) + ", " + solution_string + " }";
    }

protected:
    std::vector<T> data_;
};

#endif //ECL_VECTOR_BASED_SOLUTION_HPP
