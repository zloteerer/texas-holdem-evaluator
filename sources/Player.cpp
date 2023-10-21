#include "Player.hpp"

Player::Player(const std::string &name, std::vector<poker::Card> hand):
    _name(name), _hand(hand)
{}
Player::~Player() {}

void Player::addCard(poker::Card card) {
    this->_hand.push_back(card);
}

void Player::sortHand() {
    std::sort(this->_hand.begin(), this->_hand.end());
}

std::string Player::getName() const {
    return this->_name;
}
std::vector<poker::Card> Player::getHand() const {
    return this->_hand;
}

std::unordered_map<int, int> Player::getRankCount() {
    if (this->_countRank.size() <= 0)
        for (const auto &card: this->_hand)
            this->_countRank[card.getRank()] += 1;
    return this->_countRank;
}

std::unordered_map<int, int> Player::getSuitCount() {
    if (this->_countSuit.size() <= 0)
        for (const auto &card: this->_hand)
            this->_countSuit[card.getSuit()] += 1;
    return this->_countSuit;
}
