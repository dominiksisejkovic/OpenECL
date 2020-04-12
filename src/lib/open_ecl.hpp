// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef ECL_OPEN_ECL_HPP
#define ECL_OPEN_ECL_HPP

#include "../utils/property_reader.hpp"
#include "../utils/algorithm_factory.hpp"

void printHeader() {
    std::cout << "#######################################################################" << std::endl;
    std::cout << "#    OpenECL: The Free Evolutionary Computation Library for C++       #" << std::endl;
    std::cout << "#                 (c) 2020 Dominik Šišejković                         #" << std::endl;
    std::cout << "#######################################################################" << std::endl;
}

bool loadProperties(int argc, char *argv[]) {
    printHeader();

    if (argc != 2) {
        std::cout << "evo-lib expects one argument. Run as follows:" << std::endl;
        std::cout << "\t ./evo-lib <evo.properties.file>" << std::endl;
        return false;
    }

    if (!utils::io::fileExists(argv[1])) {
        std::cout << "Properties file not found: " << argv[1] << std::endl;
        return false;
    }

    // Load properties
    PropertyReader::getInstance().load(argv[1]);
    return true;
}


#endif //ECL_OPEN_ECL_HPP
