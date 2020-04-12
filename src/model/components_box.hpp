// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_COMPONENTS_BOX_HPP
#define OPEN_ECL_COMPONENTS_BOX_HPP

#include <memory>
#include "operators/operators_model.hpp"
#include "i_population_generator.hpp"
#include <unordered_map>

class ComponentsBox {
public:
    ~ComponentsBox() {}

    ComponentsBox() {}

    const std::shared_ptr<ISelection> &getSelection() const {
        return selection_;
    }

    void setSelection(const std::shared_ptr<ISelection> &selection) {
        selection_ = selection;
    }

    const std::shared_ptr<IMutation> &getMutation() const {
        return mutation_;
    }

    void setMutation(const std::shared_ptr<IMutation> &mutation) {
        mutation_ = mutation;
    }

    const std::shared_ptr<ICrossover> &getCrossover() const {
        return crossover_;
    }

    void setCrossover(const std::shared_ptr<ICrossover> &crossover) {
        crossover_ = crossover;
    }

    const std::shared_ptr<IPopulationGenerator> &getPopulationGenerator() const {
        return population_generator_;
    }

    void setPopulationGenerator(const std::shared_ptr<IPopulationGenerator> &population_generator) {
        population_generator_ = population_generator;
    }

    const std::shared_ptr<IReplacement> &getReplacement() const {
        return replacement_;
    }

    void setReplacement(const std::shared_ptr<IReplacement> &replacement) {
        replacement_ = replacement;
    }

private:
    std::shared_ptr<ISelection> selection_;
    std::shared_ptr<IMutation> mutation_;
    std::shared_ptr<ICrossover> crossover_;
    std::shared_ptr<IReplacement> replacement_;
    std::shared_ptr<IPopulationGenerator> population_generator_;
};

#endif //OPEN_ECL_COMPONENTS_BOX_HPP
