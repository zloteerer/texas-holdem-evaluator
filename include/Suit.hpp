#ifndef SUIT_HPP_
#define SUIT_HPP_

#include <unordered_map>

namespace poker {
    class Suit {
        public:
            enum Value {
                Hearts,
                Diamonds,
                Spades,
                Clubs
            };

            std::unordered_map<char, Value> letters = {
                {'h', Value::Hearts},
                {'d', Value::Diamonds},
                {'s', Value::Spades},
                {'c', Value::Clubs},
            };

            std::unordered_map<Value, std::string> to_representation = {
                {Value::Hearts, "Hearts"},
                {Value::Diamonds, "Diamonds"},
                {Value::Spades, "Spades"},
                {Value::Clubs, "Clubs"},
            };

            std::unordered_map<Value, std::string> to_symbol_representation = {
                {Value::Hearts, "♥"},
                {Value::Diamonds, "♦"},
                {Value::Spades, "♠"},
                {Value::Clubs, "♣"},
            };
    };
}

#endif /* !SUIT_HPP_ */
