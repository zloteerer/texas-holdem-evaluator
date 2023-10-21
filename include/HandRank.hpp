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

            std::unordered_map<Value, std::string> to_representation = {
                {Value::HighCard, "High Card"},
                {Value::Pair, "Pair"},
                {Value::TwoPairs, "Two pairs"},
                {Value::ThreeOfAKind, "Three of a Kind"},
                {Value::Straight, "Straight"},
                {Value::Flush, "Flush"},
                {Value::FullHouse, "Full House"},
                {Value::FourOfAKind, "Four of a Kind"},
                {Value::StraightFlush, "Straight Flush"},
                {Value::RoyalFlush, "Royal Flush"},
            };

        private:
            std::bitset<52> _duplicates;
            std::bitset<13> _values;
    };
}

#endif /* !HANDRANK_HPP_ */
