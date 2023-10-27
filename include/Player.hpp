#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include <iostream>

#include "Card.hpp"
#include "Utils.hpp"

class Player {
    public:
        Player();
        Player(const Player &copy);
        Player(const std::string &name);
        ~Player();

        void addCard(poker::Card card);
        void addBoard(std::bitset<60> bits);
        void sortHand();
        int handScore(std::bitset<60> bits_hand, std::bitset<60> bits_values, std::bitset<15> bits_count);
        unsigned long tiesScore(std::bitset<60> bits_values);

        std::string getName() const;
        std::bitset<60> getHand() const;
        std::bitset<15> getHandCount() const;
        int getScore() const;
        int getTiesScore() const;
        std::bitset<60> getBestHand() const;

        void setScore(int score);
        void setTiesScore(int score);
        void setBestHand(std::bitset<60> bits);
    private:
        std::string _name;

        std::bitset<60> _hand;
        std::bitset<15> _hand_count;

        std::bitset<60> _best_hand;

        int _score = 0;
        int _ties_score = 0;
};

#endif /* !PLAYER_HPP_ */
