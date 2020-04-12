//
// Created by dsisejkovic on 02.04.20.
//

#ifndef OPEN_ECL_K_TOURNAMENT_SELECTION_HPP
#define OPEN_ECL_K_TOURNAMENT_SELECTION_HPP

#include "../../../model/operators/i_selection.hpp"

class KTournamentSelection : public ISelection {
public:
    ~KTournamentSelection() {}

    KTournamentSelection(int tournament_size, int number_of_parents) :
            tournament_size_(tournament_size), number_of_parents_(number_of_parents) {}


    std::vector<std::shared_ptr<ISolution>> execute(const std::shared_ptr<IPopulation> &population) override {
        std::vector<std::shared_ptr<ISolution>> parents;

        for (int i = 0; i < this->number_of_parents_; ++i) {
            std::vector<std::shared_ptr<ISolution>> tournament;

            for (int j = 0; j < this->tournament_size_; ++j) {
                auto selected = population->getRandomSolution();
                tournament.push_back(selected);
            }

            // Select the best parent from tournament: sort by fitness
            std::sort(
                    tournament.begin(),
                    tournament.end(),
                    [](const std::shared_ptr<ISolution> &first, const std::shared_ptr<ISolution> &second) {
                        return first->isBetterThan(second);
                    }
            );

            parents.push_back(tournament[0]);
        }

        return parents;
    }

protected:
    int tournament_size_;
    int number_of_parents_;
};

#endif //OPEN_ECL_K_TOURNAMENT_SELECTION_HPP

