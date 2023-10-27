#ifndef HANDRANK_HPP_
#define HANDRANK_HPP_

#include <unordered_map>
#include <bitset>

namespace poker {
    class HandRank {
        public:
            enum Value {
                HighCard,
                Pair,
                TwoPairs,
                ThreeOfAKind,
                Straight,
                Flush,
                FullHouse,
                FourOfAKind,
                StraightFlush,
                RoyalFlush,
            };

            std::vector<std::string> to_representation = {
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

            std::vector<int> scores = {
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
    };
}

#endif /* !HANDRANK_HPP_ */
