// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_PROPERTY_ENTRY_HPP
#define OPEN_ECL_PROPERTY_ENTRY_HPP

#include <string>

/**
 * Represents a single property entry.
 */
class PropertyEntry {
public:
    ~PropertyEntry() {}

    PropertyEntry(const std::string &entryString)
            : entry_string_(entryString) {}

    double toDouble() {
        return std::stod(this->entry_string_);
    }

    float toFloat() {
        return std::stof(this->entry_string_);
    }

    int toInteger() {
        return std::stoi(this->entry_string_);
    }

    bool toBoolean() {
        return this->entry_string_ == "true";
    }

    const std::string &toString() const {
        return this->entry_string_;
    }

private:
    std::string entry_string_;
};

#endif //OPEN_ECL_PROPERTY_ENTRY_HPP
