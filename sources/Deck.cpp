#include "Deck.hpp"

using poker::Deck;
using poker::Card;

Deck::Deck() {
    this->initialize();
}
Deck::~Deck() {}

std::vector<Card> Deck::getCards() const {
    return this->_cards;
}

void Deck::initialize() {
    this->_cards.clear();
    for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Clubs); suit++)
        for (int rank = static_cast<int>(Rank::Ace); rank <= static_cast<int>(Rank::King); rank++)
            this->_cards.push_back(Card(static_cast<Rank::Value>(rank), static_cast<Suit::Value>(suit)));
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->_cards.begin(), this->_cards.end(), std::default_random_engine(seed));
}

Card Deck::_deal_card() {
    Card card = this->_cards.back();

    this->_cards.pop_back();
    return card;
}

std::vector<Card> Deck::dealFlop() {
    std::vector<Card> vector;

    for (std::size_t i = 0; i < 3; i++)
        vector.push_back(this->_deal_card());
    return vector;
}

Card Deck::dealTurn() {
    return this->_deal_card();
}

Card Deck::dealRiver() {
    return this->_deal_card();
}

bool Deck::removeCard(Rank::Value rank, Suit::Value suit) {
    for (auto card = this->_cards.begin(); card != this->_cards.end(); card++) {
        if ((*card).getRank() == rank && (*card).getSuit() == suit) {
            this->_cards.erase(card);
            return true;
        }
    }
    return false;
}