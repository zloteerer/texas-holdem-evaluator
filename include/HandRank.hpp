#ifndef HANDRANK_HPP_
#define HANDRANK_HPP_

#include <unordered_map>
#include <bitset>

namespace poker {
    static std::vector<int> hand_rank_scores = {
        7, // four of a kind
        5, // flush
        4, // straight
        8, // straight flush
        0, // high card
        1, // one pair
        2, // two pairs
        9, // royal flush
        3, // three of a kind
        6 // full house
    };

    const static std::vector<std::string> hand_rank_to_representation = {
        {"High Card"},
        {"Pair"},
        {"Two pairs"},
        {"Three of a Kind"},
        {"Straight"},
        {"Flush"},
        {"Full House"},
        {"Four of a Kind"},
        {"Straight Flush"},
        {"Royal Flush"},
    };
}

#endif /* !HANDRANK_HPP_ */
