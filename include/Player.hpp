#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#define LENGTH_VALUES_BITSET 60
#define LENGTH_COUNT_BITSET 15
#define LENGTH_TIES_BITSET 20

#include <vector>
#include <string>
#include <iostream>

#include "Utils.hpp"

class Player {
    public:
        Player();
        Player(const Player &copy);
        Player(const std::string &name);
        ~Player();

        void addCard(int rank, int suit);
        void addBoard(std::bitset<LENGTH_VALUES_BITSET> bits);
        void sortHand();
        int handScore(
            std::bitset<LENGTH_VALUES_BITSET> bits_hand,
            std::bitset<LENGTH_VALUES_BITSET> bits_values,
            std::bitset<LENGTH_COUNT_BITSET> bits_count
        );
        unsigned long tiesScore(std::bitset<LENGTH_VALUES_BITSET> bits_values);

        std::string getName() const;
        std::bitset<LENGTH_VALUES_BITSET> getHand() const;
        std::bitset<LENGTH_COUNT_BITSET> getHandCount() const;
        int getScore() const;
        int getTiesScore() const;
        std::bitset<LENGTH_VALUES_BITSET> getBestHand() const;

        void setScore(int score);
        void setTiesScore(int score);
        void setBestHand(std::bitset<LENGTH_VALUES_BITSET> bits);
    private:
        std::string _name;

        std::bitset<LENGTH_VALUES_BITSET> _hand;
        std::bitset<LENGTH_COUNT_BITSET> _hand_count;

        std::bitset<LENGTH_VALUES_BITSET> _best_hand;

        int _score = 0;
        int _ties_score = 0;
};

#endif /* !PLAYER_HPP_ */
