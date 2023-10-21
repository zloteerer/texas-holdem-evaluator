#include "Card.hpp"

using poker::Card;

Card::Card(Rank::Value rank, Suit::Value suit): _rank(rank), _suit(suit) {}
Card::Card(char rank, char suit) {
    std::unordered_map<char, poker::Rank::Value> ranks = poker::Rank().letters;
    std::unordered_map<char, poker::Suit::Value> suits = poker::Suit().letters;

    this->_rank = ranks[rank];
    this->_suit = suits[suit];
}
Card::~Card() {}

bool Card::operator<(const Card &card) const {
    return this->_rank == card._rank ? this->_suit < card._suit : this->_rank < card._rank;
}

poker::Rank::Value Card::getRank() const {
    return this->_rank;
}

poker::Suit::Value Card::getSuit() const {
    return this->_suit;
}

std::string Card::to_symbol_representation() const {
    return std::string(poker::Rank().to_symbol_representation[this->_rank] + poker::Suit().to_symbol_representation[this->_suit]);
}

std::string Card::to_representation() const {
    return std::string(poker::Rank().to_representation[this->_rank] + " of " + poker::Suit().to_representation[this->_suit]);
}