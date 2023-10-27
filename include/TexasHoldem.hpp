#ifndef TEXASHOLDEM_HPP_
#define TEXASHOLDEM_HPP_

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Deck.hpp"
#include "HandRank.hpp"
#include "String.hpp"
#include "Utils.hpp"

namespace poker {
    class TexasHoldem {
        public:
            TexasHoldem(int ac, char **av);
            ~TexasHoldem();

            Player winner();
            void play();
        private:
            void _parseBoard(std::string str);
            Player _parsePlayer(std::string str);
            Card _readCard(char rank, char suit);
            void _handleArguments(int ac, char **av);
            void _usage();

            std::vector<Player> _players;

            std::bitset<60> _deck;
            std::bitset<60> _board;
            std::bitset<15> _board_values;
            poker::HandRank _hand_rank;
    };
}

#endif /* !TEXASHOLDEM_HPP_ */
