#ifndef TEXASHOLDEM_HPP_
#define TEXASHOLDEM_HPP_

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "HandRank.hpp"
#include "String.hpp"
#include "Utils.hpp"

namespace poker {
    class TexasHoldem {
        public:
            TexasHoldem(int ac, char **av);
            ~TexasHoldem();

            std::vector<Player> winner();
            void play();
        private:
            void _parse_board(std::string str);
            Player _parse_player(std::string str);
            int _read_rank(char rank);
            int _read_suit(char suit);
            void _handle_arguments(int ac, char **av);
            void _usage();

            std::vector<Player> _players;

            std::bitset<60> _deck;
            std::bitset<60> _board;
            std::bitset<15> _board_values;
    };
}

#endif /* !TEXASHOLDEM_HPP_ */
