#ifndef DECK_HPP_
#define DECK_HPP_

#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "Card.hpp"

namespace poker {
    class Deck {
        public:
            Deck();
            ~Deck();

            std::vector<Card> getCards() const;

            void initialize();
            void shuffle();

            std::vector<Card> dealFlop();
            Card dealTurn();
            Card dealRiver();

            bool removeCard(Rank::Value rank, Suit::Value suit);
        private:
            Card _deal_card();

            std::vector<Card> _cards;
    };
}

#endif /* !DECK_HPP_ */
