#ifndef TEXASHOLDEM_HPP_
#define TEXASHOLDEM_HPP_

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Deck.hpp"
#include "HandRank.hpp"
#include "String.hpp"

namespace poker {
    class TexasHoldem {
        public:
            TexasHoldem(int ac, char **av);
            ~TexasHoldem();

            void addPlayer(std::string, std::vector<Card>);
            void addPlayersCard(Card);
            void sortPlayersHand();
            poker::HandRank::Value getHandRanking(Player);

            void winner();
            void play();
        private:
            std::vector<Card> _parseBoard(std::string str);
            Player _parsePlayer(std::string str);
            Card _readCard(char rank, char suit);
            void _handleArguments(int ac, char **av);
            void _usage();

            std::unique_ptr<Deck> _deck = std::make_unique<Deck>();
            std::vector<Player> _players;
            std::vector<Card> _board;
    };
}

#endif /* !TEXASHOLDEM_HPP_ */
