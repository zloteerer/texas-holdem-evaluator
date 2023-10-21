#include "TexasHoldem.hpp"

using poker::TexasHoldem;

TexasHoldem::TexasHoldem(int ac, char **av) {
    this->_handleArguments(ac, av);
}
TexasHoldem::~TexasHoldem() {}

void TexasHoldem::_usage() {
}

poker::Card TexasHoldem::_readCard(char rank, char suit) {
    if (Rank().letters.count(rank) <= 0 || Suit().letters.count(suit) <= 0)
        throw std::runtime_error("Bad card entry.");
    return Card(rank, suit);
}

std::vector<poker::Card> TexasHoldem::_parseBoard(std::string str) {
    // number of characters must be 6 or 8 or 10 (flop/turn/river)
    if (str.size() != 6 && str.size() != 8 && str.size() != 10)
        throw std::runtime_error("Board must have either 3, 4 or 5 cards.");

    std::vector<poker::Card> cards;

    for (std::size_t i = 0; i < str.size(); i += 2)
        cards.push_back(this->_readCard(str[i], str[i + 1]));

    for (const auto &i: cards)
        if (!(this->_deck.get()->removeCard(i.getRank(), i.getSuit())))
            throw std::runtime_error("Card already distributed.");
    return cards;
}

Player TexasHoldem::_parsePlayer(std::string str) {
    // number of characters must be 4 (2 cards)
    if (str.size() != 4)
        throw std::runtime_error("A player must have 2 cards.");

    std::vector<poker::Card> cards;

    for (std::size_t i = 0; i < str.size(); i += 2)
        cards.push_back(this->_readCard(str[i], str[i + 1]));
    for (const auto &i: cards)
        if (!(this->_deck.get()->removeCard(i.getRank(), i.getSuit())))
            throw std::runtime_error("Card already distributed.");
    return Player(std::string("p" + std::to_string(this->_players.size() + 1)), cards);
}

void TexasHoldem::_handleArguments(int ac, char **av) {
    std::vector<std::string> args;

    if (ac > 1) {
        args.assign(av + 1, av + ac);
    } else {
        throw std::runtime_error("Not enough arguments. Try --help or -h.");
    }

    for (std::size_t i = 0; i < args.size(); i++) {
        if (compare("--help", args[i]) || compare("-h", args[i])) {
            this->_usage();
            std::exit(0);
        } else if (compare("--board", args[i]) || compare("-b", args[i])) {
            // case when --board was already given
            // first occurence has the priority
            if (this->_board.size() > 0) continue;

            if (i + 1 < args.size())
                this->_board = this->_parseBoard(args[i + 1]);
            else
                throw std::runtime_error("Not enough arguments. Try --help or -h.");

            // it allows to jump the cards
            i += 1;
        } else if (compare("--player", args[i]) || compare("-p", args[i])) {
            if (i + 1 < args.size())
                this->_players.push_back(this->_parsePlayer(args[i + 1]));
            else
                throw std::runtime_error("Not enough arguments. Try --help or -h.");

            // it allows to jump the cards
            i += 1;
        } else {
            throw std::runtime_error("Not enough arguments. Try --help or -h.");
        }
    }

    // when all cards are distributed, shuffle deck
    this->_deck.get()->shuffle();
}

void TexasHoldem::addPlayer(std::string name, std::vector<Card> hand) {
    if (!this->_deck->removeCard(hand.at(0).getRank(), hand.at(0).getSuit()))
        throw std::runtime_error("Duplicate card.");
    if (!this->_deck->removeCard(hand.at(1).getRank(), hand.at(1).getSuit()))
        throw std::runtime_error("Duplicate card.");
    this->_players.push_back(Player(name, hand));
}

void TexasHoldem::addPlayersCard(Card card) {
    for (auto &player: this->_players)
        player.addCard(card);
    this->sortPlayersHand();
}

void TexasHoldem::play() {
    for (const auto &card: this->_board) {
        this->addPlayersCard(card);
    }
    this->winner();
}

void TexasHoldem::winner() {
    for (const auto &player: this->_players) {
        std::cout << player.getName() << " -> " << poker::HandRank().to_representation[this->getHandRanking(player)] << std::endl;
    }
}

void TexasHoldem::sortPlayersHand() {
    for (auto &player: this->_players)
        player.sortHand();
}

poker::HandRank::Value TexasHoldem::getHandRanking(Player player) {
    std::vector<Card> cards = player.getHand();
    std::unordered_map<int, int> countRank = player.getRankCount();
    std::unordered_map<int, int> countSuit = player.getSuitCount();

    for (const auto &card: cards) {
        std::cout << card.to_symbol_representation() << ",";
    }
    for (const auto &[rank, count]: countRank) {
        std::cout << poker::Rank().to_symbol_representation[static_cast<poker::Rank::Value>(rank)] << ":" << count << " ";
    }
    std::cout << std::endl;

    bool hasPair = false;
    bool hasTwoPair = false;
    bool hasThreeOfAKind = false;
    bool hasStraight = false;
    bool hasFlush = false;
    bool hasFullHouse = false;
    bool hasStraightFlush = false;
    bool hasRoyalFlush = false;
    int pairNumber = 0;

    // hand ranking happens only when the player has 7 cards (the hand + board ones)
    if (this->_board.size() != 5)
        throw std::runtime_error("Cannot determine who won with less than 5 cards in the board.");

    // faire la straight pour les couleurs et la straight sans
    for (std::size_t i = 0; i < cards.size(); i++) {
        if (i + 5 > cards.size()) break;
        if (
            (cards[i].getRank() + 1) == cards[i + 1].getRank() && \
            (cards[i + 1].getRank() + 1) == cards[i + 2].getRank() && \
            (cards[i + 2].getRank() + 1) == cards[i + 3].getRank() && \
            (cards[i + 3].getRank() + 1) == cards[i + 4].getRank()
        ) {
            if (
                cards[i].getSuit() == cards[i + 1].getSuit() && \
                cards[i + 1].getSuit() == cards[i + 2].getSuit() && \
                cards[i + 2].getSuit() == cards[i + 3].getSuit() && \
                cards[i + 3].getSuit() == cards[i + 4].getSuit()
            ) {
                if (cards[i].getRank() == poker::Rank::Ten)
                    return poker::HandRank::RoyalFlush;
                hasStraightFlush = true;
            }
            hasStraight = true;
        }
    }

    // start by checking the more powerful to stop if true
    // otherwise cannot stop if it starts from the less powerful

    // check si la suite commence par 10
    if (hasStraightFlush) return poker::HandRank::StraightFlush;

    for (const auto &[rank, count]: countRank) {
        if (count == 2) {
            hasPair = true;
            pairNumber += 1;
        } else if (count == 3) {
            hasThreeOfAKind = true;
        } else if (count == 4) {
            return poker::HandRank::FourOfAKind;
        }
    }

    if (hasThreeOfAKind == true && pairNumber >= 1) {
        return poker::HandRank::FullHouse;
    }

    for (const auto &[suit, count]: countSuit) {
        if (count >= 5)
            return poker::HandRank::Flush;
    }

    if (hasStraight == true)
        return poker::HandRank::Straight;

    if (hasThreeOfAKind == true && pairNumber <= 0) {
        return poker::HandRank::ThreeOfAKind;
    }

    if (pairNumber >= 2)
        return poker::HandRank::TwoPairs;
    else if (pairNumber == 1)
        return poker::HandRank::Pair;
    return poker::HandRank::HighCard;
}
