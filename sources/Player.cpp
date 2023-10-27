#include "Player.hpp"

Player::Player(const std::string &name):
    _name(name)
{}
Player::Player() {}
Player::Player(const Player &copy) {
    _name = copy._name;

    _hand = copy._hand;
    _hand_count = copy._hand_count;
    _best_hand = copy._best_hand;

    _score = copy._score;
    _ties_score = copy._ties_score;
}

Player::~Player() {}

void Player::addCard(poker::Card card) {
    if (this->_hand[(card.getRank() * 4) + card.getSuit()] == 1)
        throw std::runtime_error("This player already have this card.");
    this->_hand.set(card.getRank() * 4 + card.getSuit());

    pushRankToBitset(this->_hand_count, card.getRank());
}

void Player::addBoard(std::bitset<60> bits) {
    this->_hand = this->_hand | bits;
    for (std::size_t i = 0; i < 60; i += 4)
        if (bits[i] == 1 || bits[i + 1] == 1 || bits[i + 2] == 1 || bits[i + 3] == 1)
            this->_hand_count.set(i / 4);
}

int Player::handScore(
    std::bitset<60> bits_hand,
    std::bitset<60> bits_values,
    std::bitset<15> bits_count
) {
    int suit_value = -1;
    bool is_flush = true;
    bool is_flush_royal = false;
    bool is_straight = false;
    bool is_straight_flush = false;

    // flush check
    for (std::size_t i = 0; i < bits_values.size(); i++) {
        if (bits_values[i] != 1) continue;
        if (suit_value != -1 && i % 4 != suit_value)
            is_flush = false;
        else
            suit_value = i % 4;
    }

    // straight check
    int count = 0;
    for (int i = 0; i < bits_count.size(); ++i)
        if (bits_count[i] == 1) {
            count += 1;
            if (count >= 5) {
                is_straight = true;
                break;
            }
        } else {
            count = 0;
        }

    // ace low check
    if (bits_count == 16444)
        is_straight = true;

    // royal flush check
    if (is_flush == true && bits_count == 31744)
        return 8;

    // straight flush check
    if (is_flush == true && is_straight == true)
        return 4;

    if (is_flush == true)
        return 2;

    if (is_straight == true)
        return 3;

    return bits_hand.to_ullong() % 15;
}

unsigned long Player::tiesScore(std::bitset<60> bits_values) {
    std::vector<int> cards;
    std::bitset<20> result;
    std::bitset<4> value_bitset;
    int bit_position = 0;

    for (std::size_t i = 0; i < bits_values.size(); i++)
        if (bits_values[i] == 1)
            cards.push_back((i - (i % 4)) / 4);

    for (int i = 0; i < cards.size(); ++i) {
        int value = cards[i] & 0x0F;
        std::bitset<4> value_bitset(value);

        for (int j = 0; j < 4; ++j) {
            result[bit_position] = value_bitset[j];
            bit_position++;
        }
    }
    return result.to_ulong();
}

std::string Player::getName() const {
    return this->_name;
}

std::bitset<60> Player::getHand() const {
    return this->_hand;
}

std::bitset<15> Player::getHandCount() const {
    return this->_hand_count;
}

std::bitset<60> Player::getBestHand() const {
    return this->_best_hand;
}

int Player::getScore() const {
    return this->_score;
}

int Player::getTiesScore() const {
    return this->_ties_score;
}

void Player::setScore(int score) {
    this->_score = score;
}

void Player::setTiesScore(int score) {
    this->_ties_score = score;
}

void Player::setBestHand(std::bitset<60> bits) {
    this->_best_hand = bits;
}