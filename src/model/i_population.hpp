// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_I_POPULATION_HPP
#define OPEN_ECL_I_POPULATION_HPP

#include <memory>
#include <vector>
#include "solution/i_solution.hpp"
#include "../utils/random_utils.hpp"

class IPopulation {
public:
    ~IPopulation() {}

    IPopulation() {}

    const std::vector<std::shared_ptr<ISolution>> &getSolutions() const {
        return solutions_;
    }

    int getIndexOf(const std::shared_ptr<ISolution> &solution) {
        int index = -1;
        auto size = getSize();
        for (int i = 0; i < size; ++i) {
            if (solutions_[i] == solution) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            throw std::runtime_error("Solution not found in population.");
        }

        return index;
    }

    int getIndexOfBestSolution() const {
        int index_best = 0;
        auto tmp_fitness = solutions_[0]->getFitness();

        auto size = getSize();
        for (int i = 1; i < size; ++i) {
            auto fitness_i = solutions_[i]->getFitness();
            if (fitness_i->isBetterThan(tmp_fitness)) {
                tmp_fitness = fitness_i;
                index_best = i;
            }
        }

        return index_best;
    }

    const std::shared_ptr<ISolution> &getBestSolution() const {
        return solutions_[this->getIndexOfBestSolution()];
    }

    int getIndexOfWorstSolution() const {
        int index_worst = 0;
        auto tmp_fitness = solutions_[0]->getFitness();

        auto size = getSize();
        for (int i = 1; i < size; ++i) {
            auto fitness_i = solutions_[i]->getFitness();
            if (fitness_i->isWorseThan(tmp_fitness)) {
                tmp_fitness = fitness_i;
                index_worst = i;
            }
        }

        return index_worst;
    }

    const std::shared_ptr<ISolution> &getWorstSolution() const {
        return solutions_[this->getIndexOfWorstSolution()];
    }

    void replaceSolution(const std::shared_ptr<ISolution> &old_solution,
                         const std::shared_ptr<ISolution> &new_solution) {
        auto index_old = getIndexOf(old_solution);
        this->solutions_[index_old] = new_solution;
    }

    void replaceSolutions(const std::vector<std::shared_ptr<ISolution>> &new_solutions) {
        this->solutions_ = new_solutions;
    }

    const std::shared_ptr<ISolution> &getSolutionOnIndex(int index) const {
        if (index < 0 || index > getSize() - 1) {
            throw std::runtime_error("IPopulation: index out of range.");
        }

        return solutions_[index];
    }

    int getRandomSolutionIndex() const {
        return RandomUtils::getInstance().randomIntInRange(0, getSize() - 1);
    }

    const std::shared_ptr<ISolution> &getRandomSolution() const {
        auto index = getRandomSolutionIndex();
        return solutions_[index];
    }

    void registerSolution(const std::shared_ptr<ISolution> &solution) {
        solutions_.push_back(solution);
    }

    int getSize() const {
        return static_cast<int>(solutions_.size());
    }

    void replaceWorstSolutionWith(const std::shared_ptr<ISolution> &solution) {
        auto index_worst = getIndexOfWorstSolution();
        solutions_[index_worst] = solution;
    }

private:
    std::vector<std::shared_ptr<ISolution>> solutions_;
};

#endif //OPEN_ECL_I_POPULATION_HPP
