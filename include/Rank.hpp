#ifndef RANK_HPP_
#define RANK_HPP_

#include <unordered_map>

namespace poker {
    class Rank {
        public:
            enum Value {
                Two = 2,
                Three,
                Four,
                Five,
                Six,
                Seven,
                Eight,
                Nine,
                Ten,
                Jack,
                Queen,
                King,
                Ace
            };

            std::unordered_map<char, Value> letters = {
                {'2', Value::Two},
                {'3', Value::Three},
                {'4', Value::Four},
                {'5', Value::Five},
                {'6', Value::Six},
                {'7', Value::Seven},
                {'8', Value::Eight},
                {'9', Value::Nine},
                {'t', Value::Ten},
                {'j', Value::Jack},
                {'q', Value::Queen},
                {'k', Value::King},
                {'a', Value::Ace},
            };

            std::unordered_map<Value, std::string> to_representation = {
                {Value::Two, "2"},
                {Value::Three, "3"},
                {Value::Four, "4"},
                {Value::Five, "5"},
                {Value::Six, "6"},
                {Value::Seven, "7"},
                {Value::Eight, "8"},
                {Value::Nine, "9"},
                {Value::Ten, "Ten"},
                {Value::Jack, "Jack"},
                {Value::Queen, "Queen"},
                {Value::King, "King"},
                {Value::Ace, "Ace"},
            };

            std::unordered_map<Value, std::string> to_symbol_representation = {
                {Value::Two, "2"},
                {Value::Three, "3"},
                {Value::Four, "4"},
                {Value::Five, "5"},
                {Value::Six, "6"},
                {Value::Seven, "7"},
                {Value::Eight, "8"},
                {Value::Nine, "9"},
                {Value::Ten, "T"},
                {Value::Jack, "J"},
                {Value::Queen, "Q"},
                {Value::King, "K"},
                {Value::Ace, "A"},
            };
    };
}

#endif /* !RANK_HPP_ */
