#ifndef RANK_HPP_
#define RANK_HPP_

#include <unordered_map>

namespace poker {
    static std::unordered_map<char, int> rank_letters = {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'t', 10},
        {'j', 11},
        {'q', 12},
        {'k', 13},
        {'a', 14},
    };

    const static std::vector<std::string> rank_to_representation = {
        {"Nan"},
        {"Nan"},
        {"2"},
        {"3"},
        {"4"},
        {"5"},
        {"6"},
        {"7"},
        {"8"},
        {"9"},
        {"Ten"},
        {"Jack"},
        {"Queen"},
        {"King"},
        {"Ace"},
    };

    const static std::vector<std::string> rank_to_symbol_representation = {
        {"Nan"},
        {"Nan"},
        {"2"},
        {"3"},
        {"4"},
        {"5"},
        {"6"},
        {"7"},
        {"8"},
        {"9"},
        {"T"},
        {"J"},
        {"Q"},
        {"K"},
        {"A"},
    };
}

#endif /* !RANK_HPP_ */
