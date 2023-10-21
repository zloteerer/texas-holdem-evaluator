#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include <iostream>

#include "Card.hpp"

class Player {
    public:
        Player(const std::string &name, std::vector<poker::Card>);
        ~Player();

        void addCard(poker::Card card);
        void sortHand();

        std::string getName() const;
        std::vector<poker::Card> getHand() const;
        std::unordered_map<int, int> getRankCount();
        std::unordered_map<int, int> getSuitCount();

    private:
        const std::string _name;
        std::vector<poker::Card> _hand;
        std::unordered_map<int, int> _countSuit;
        std::unordered_map<int, int> _countRank;
};

#endif /* !PLAYER_HPP_ */
