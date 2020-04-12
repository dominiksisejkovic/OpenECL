// (c) 2020 Dominik Šišejković
// This code is licensed under the MIT license (see LICENSE.txt for details)

#ifndef OPEN_ECL_DATA_UTILS_HPP
#define OPEN_ECL_DATA_UTILS_HPP

#include <string>
#include <regex>
#include <fstream>

namespace utils {

    namespace strings {

        inline bool startsWith(std::string const &arg, std::string const &prefix) {
            return !arg.compare(0, prefix.size(), prefix);
        }

        inline void trimLeft(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        }

        inline void trimRight(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end()
            );
        }

        inline std::string trimAndReturn(std::basic_string<char, std::char_traits<char>, std::allocator<char>> s) {
            trimLeft(s);
            trimRight(s);

            return s;
        }

        inline void trim(std::string &s) {
            trimLeft(s);
            trimRight(s);
        }

        inline std::string clean(std::basic_string<char, std::char_traits<char>, std::allocator<char>> s) {
            // Remove multiple spaces
            std::regex re("\\s{2,}");
            std::string s1 = regex_replace(s, re, " ");

            return trimAndReturn(s1);
        }

        template<typename T>
        inline void split(const std::string &s, char delimiter, T result) {
            std::stringstream s_stream;
            s_stream.str(s);
            std::string item;

            while (std::getline(s_stream, item, delimiter)) {
                *(result++) = item;
            }
        }

        inline std::vector<std::string> split(std::string const &s, char delimiter) {
            std::vector<std::string> elems;
            split(s, delimiter, std::back_inserter(elems));
            return elems;
        }
    }

    namespace io {
        inline std::vector<std::string> readFile(const std::string &file_name) {
            std::ifstream input_file(file_name);
            if (!input_file.is_open()) {
                input_file.close();
                throw std::runtime_error("ReadFile: could not open file.");
            }

            std::vector<std::string> content;

            std::string line;
            while (std::getline(input_file, line)) {
                content.push_back(line + "\n");
            }

            input_file.close();

            return content;
        }

        inline bool fileExists(const std::string &file_name) {
            std::ifstream infile(file_name);
            return infile.good();
        }
    }
}


#endif //OPEN_ECL_DATA_UTILS_HPP
