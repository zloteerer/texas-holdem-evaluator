#ifndef SUIT_HPP_
#define SUIT_HPP_

#include <unordered_map>

namespace poker {
    static std::unordered_map<char, int> suit_letters = {
        {'h', 0},
        {'d', 1},
        {'s', 2},
        {'c', 3},
    };

    const static std::vector<std::string> suit_to_representation = {
        {"Hearts"},
        {"Diamonds"},
        {"Spades"},
        {"Clubs"},
    };

    const static std::vector<std::string> suit_to_symbol_representation = {
        {"♥"},
        {"♦"},
        {"♠"},
        {"♣"},
    };
}

#endif /* !SUIT_HPP_ */
