// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)


#ifndef OPEN_ECL_PROPERTY_READER_HPP
#define OPEN_ECL_PROPERTY_READER_HPP

#include "data_utils.hpp"
#include "property_entry.hpp"
#include <string>
#include <unordered_map>
#include <iostream>

/**
 * Singleton state storing all property values.
 */
class PropertyReader {
public:

    /**
     * Registers a new value in the properties map.
     * @param key Key for storing the entry.
     * @param value Value of the entry to be stored.
     */
    void registerEntry(std::string const &key, std::string value) {
        properties_[key] = std::make_shared<PropertyEntry>(value);
    }

    /**
     * Gets the entry stored under the given key.
     * @param key Key of the entry.
     * @return PropertyEntry
    */
    std::shared_ptr<PropertyEntry> getEntry(std::string const &key) {
        auto it = properties_.find(key);
        if (it == properties_.end()) {
            throw std::runtime_error("PropertiesReader not containing value for key: " + key);
        }

        return it->second;
    }

    static PropertyReader &getInstance() {
        static PropertyReader instance_;
        return instance_;
    }

    /**
     * Loads the properties stored in the given file.
     * @param file_name Name of file.
     */
    void load(std::string const &file_name) {
        auto lines = utils::io::readFile(file_name);

        for (auto &line : lines) {
            auto pre_processed = utils::strings::clean(line);

            if (pre_processed.empty() || utils::strings::startsWith(pre_processed, "#")) {
                continue;
            }

            auto parts = utils::strings::split(pre_processed, '=');
            auto key = utils::strings::clean(parts[0]);
            auto value = utils::strings::clean(parts[1]);

            PropertyReader::getInstance().registerEntry(key, value);
        }
    }

    /**
     * Prints all stored properties.
     */
    void printAllProperties() {
        std::for_each(
                properties_.begin(),
                properties_.end(),
                [](std::pair<std::string, std::shared_ptr<PropertyEntry>> entry) {
                    std::cout << entry.first << " = " << entry.second << std::endl;
                }
        );
    }

protected:
    ~PropertyReader() {}

    PropertyReader() {}

    // delete copy and move constructors and assign operators
    PropertyReader(PropertyReader const &) = delete;             // Copy construct
    PropertyReader(PropertyReader &&) = delete;                  // Move construct
    PropertyReader &operator=(PropertyReader const &) = delete;  // Copy assign
    PropertyReader &operator=(PropertyReader &&) = delete;      // Move assign

    static PropertyReader *instance_;

    std::unordered_map<std::string, std::shared_ptr<PropertyEntry>> properties_;

};


#endif //OPEN_ECL_PROPERTY_READER_HPP
