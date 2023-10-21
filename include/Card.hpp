#ifndef CARD_HPP_
#define CARD_HPP_

#include <iostream>

#include "Rank.hpp"
#include "Suit.hpp"

namespace poker {
    class Card {
        public:
            Card(Rank::Value rank, Suit::Value suit);
            Card(char rank, char suit);
            ~Card();
            bool operator<(const Card &card) const;

            Rank::Value getRank() const;
            Suit::Value getSuit() const;

            std::string to_symbol_representation() const;
            std::string to_representation() const;
        private:
            Rank::Value _rank;
            Suit::Value _suit;
    };
}

#endif /* !CARD_HPP_ */
