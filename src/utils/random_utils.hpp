// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_RANDOM_UTILS_HPP
#define OPEN_ECL_RANDOM_UTILS_HPP

#include <algorithm>
#include <random>
#include <vector>
#include <set>


/**
 * Singleton class enabling access to random values generators.
 */
class RandomUtils {
public:
    ~RandomUtils() {}

    static RandomUtils &getInstance() {
        static RandomUtils instance_;
        return instance_;
    }

    /**
     * Gets a random integer in range: [from, to].
     * @param from From value.
     * @param to To value.
     * @return Random integer.
     */
    int randomIntInRange(int from, int to) {
        std::uniform_int_distribution<int> distribution(from, to);
        return distribution(rnd_source_);
    };

    /**
    * Gets a random boolean value.
    * @return Random boolean value.
    */
    bool randomBoolean() {
        std::uniform_int_distribution<int> distribution(0, 1);
        return distribution(rnd_source_) == 1;
    }

    /**
     * Gets a random double value in range [0.0, 1).
     * @return Random double.
     */
    double randomDouble() {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(rnd_source_);
    }

    /**
     * Gets a vector of unique random integers (no repetition) in range: [from, to].
     * @param n Number of values in vector.
     * @param from From value.
     * @param to To value.
     * @param sort_values If true, the resulting vector is sorted ascending.
     * @return Vector of unique int values.
     */
    std::vector<int> getNUniqueIntegersInRange(int n, int from, int to, bool sort_values) {
        if ((to - from + 1) < n) {
            throw std::runtime_error(
                    "RandomUtils: Not enough elements available ("
                    + std::to_string(to - from) + "/" + std::to_string(n) + ")"
            );
        }

        std::set<int> values;
        while (static_cast<int>(values.size()) != n) {
            auto value = randomIntInRange(from, to);

            if (values.find(value) == values.end()) {
                values.insert(value);
            }
        }

        std::vector<int> unique_values(values.begin(), values.end());
        if (sort_values) {
            std::sort(unique_values.begin(), unique_values.end());

        }

        return unique_values;
    }

    /**
     * Gets a vector of the selected size containing random boolean values.
     * @param size Size of vector.
     * @return Vector of boolean values.
     */
    std::vector<bool> randomBoolVector(int size) {
        std::vector<bool> rnd_vector;
        for (int i = 0; i < size; ++i) {
            rnd_vector.push_back(randomBoolean());
        }

        return rnd_vector;
    }

protected:
    RandomUtils() {
        std::random_device random_device;
        rnd_source_ = std::mt19937(random_device());
    }

    RandomUtils(RandomUtils const &) = delete;             // Copy construct
    RandomUtils(RandomUtils &&) = delete;                  // Move construct
    RandomUtils &operator=(RandomUtils const &) = delete;  // Copy assign
    RandomUtils &operator=(RandomUtils &&) = delete;      // Move assign

    static RandomUtils *instance_;
    std::mt19937 rnd_source_;
};

#endif //OPEN_ECL_RANDOM_UTILS_HPP
