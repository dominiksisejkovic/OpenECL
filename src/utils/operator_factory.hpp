// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_OPERATOR_FACTORY_HPP
#define OPEN_ECL_OPERATOR_FACTORY_HPP

#include <memory>
#include "../impl/operators.hpp"
#include "../model/operators/operators_model.hpp"
#include "property_reader.hpp"

/**
 * Singleton class responsible for creating evolutionary operator instances.
 */
class OperatorFactory {
public:
    static OperatorFactory &getInstance() {
        static OperatorFactory instance_;
        return instance_;
    }

    /**
     * Creates a mutation operator of the selected type.
     * @param mutation_operator_name Name of mutation operator.
     * @return Mutation instance.
     */
    std::shared_ptr<IMutation> createMutationOperator(const std::string &mutation_operator_name) {
        std::shared_ptr<IMutation> mutation_operator;

        if (mutation_operator_name == "simple.bit") {
            auto mutation_probability = PropertyReader::getInstance().getEntry(
                    "operator.mutation.simple.bit.probability")->toDouble();

            mutation_operator = std::make_shared<SimpleBitMutation>(mutation_probability);
        } else {
            throw std::runtime_error("Unsupported mutation operator: " + mutation_operator_name);
        }

        return mutation_operator;
    }

    /**
     * Creates a crossover operator of the selected type.
     * @param crossover_operator_name Name of crossover operator.
     * @return Crossover instance.
     */
    std::shared_ptr<ICrossover> createCrossoverOperator(const std::string &crossover_operator_name) {
        std::shared_ptr<ICrossover> crossover_operator;

        if (crossover_operator_name == "one.point") {
            crossover_operator = std::make_shared<OnePointCrossover>();
        } else if (crossover_operator_name == "two.point") {
            crossover_operator = std::make_shared<TwoPointCrossover>();
        } else {
            throw std::runtime_error("Unsupported crossover operator: " + crossover_operator_name);
        }

        return crossover_operator;
    }

    /**
     * Creates a mutation operator of the selected type.
     * @param mutation_operator_name Name of mutation operator.
     * @return Mutation instance.
     */
    std::shared_ptr<ISelection> createSelectionOperator(const std::string &selection_operator_name) {
        std::shared_ptr<ISelection> selection_operator;

        if (selection_operator_name == "k.tournament") {
            auto tournament_size = PropertyReader::getInstance().getEntry(
                    "operator.selection.k.tournament.size")->toInteger();
            auto num_parents = PropertyReader::getInstance().getEntry(
                    "operator.selection.k.tournament.num.parents")->toInteger();

            selection_operator = std::make_shared<KTournamentSelection>(tournament_size, num_parents);
        } else {
            throw std::runtime_error("Unsupported selection operator: " + selection_operator_name);
        }

        return selection_operator;
    }


    /**
     * Creates a replacement operator of the selected type.
     * @param replacement_operator_name Name of replacement operator.
     * @return Replacement instance.
     */
    std::shared_ptr<IReplacement> createReplacementOperator(const std::string &replacement_operator_name) {
        std::shared_ptr<IReplacement> replacement_operator;

        if (replacement_operator_name == "n.worst") {
            replacement_operator = std::make_shared<NWorstReplacement>();
        } else {
            throw std::runtime_error("Unsupported replacement operator: " + replacement_operator_name);
        }

        return replacement_operator;
    }

protected:
    ~OperatorFactory() {}

    OperatorFactory() {}

    // delete copy and move constructors and assign operators
    OperatorFactory(OperatorFactory const &) = delete;             // Copy construct
    OperatorFactory(OperatorFactory &&) = delete;                  // Move construct
    OperatorFactory &operator=(OperatorFactory const &) = delete;  // Copy assign
    OperatorFactory &operator=(OperatorFactory &&) = delete;      // Move assign

    static OperatorFactory *instance_;
};


#endif //OPEN_ECL_OPERATOR_FACTORY_HPP
