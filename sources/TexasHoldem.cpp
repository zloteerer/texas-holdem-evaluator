#include "TexasHoldem.hpp"

using poker::TexasHoldem;

TexasHoldem::TexasHoldem(int ac, char **av) {
    // set all bits to 1 except 8 first bits
    this->_deck.set();
    for (std::size_t i = 0; i < 8; i++)
        this->_deck.reset(i);

    this->_handleArguments(ac, av);
}
TexasHoldem::~TexasHoldem() {
}

void TexasHoldem::_usage() {
    std::cout << "EDIT USAGE" << std::endl;
}

poker::Card TexasHoldem::_readCard(char rank, char suit) {
    if (Rank().letters.count(rank) <= 0 || Suit().letters.count(suit) <= 0)
        throw std::runtime_error("Bad card entry.");
    return Card(rank, suit);
}

void TexasHoldem::_parseBoard(std::string str) {
    // number of characters must be 6 or 8 or 10 (flop/turn/river)
    if (str.size() != 6 && str.size() != 8 && str.size() != 10)
        throw std::runtime_error("Board must have either 3, 4 or 5 cards.");

    for (std::size_t i = 0; i < str.size(); i += 2) {
        Card card(this->_readCard(str[i], str[i + 1]));

        if (this->_deck[(card.getRank() * 4) + card.getSuit()] == 0)
            throw std::runtime_error("Card already distributed.");
        this->_deck.reset((card.getRank() * 4) + card.getSuit());
        this->_board.set((card.getRank() * 4) + card.getSuit());
    }
}

Player TexasHoldem::_parsePlayer(std::string str) {
    Player player(std::string("p" + std::to_string(this->_players.size() + 1)));

    // number of characters must be 4 (2 cards)
    if (str.size() != 4)
        throw std::runtime_error("A player must have 2 cards.");

    for (std::size_t i = 0; i < str.size(); i += 2) {
        Card card(this->_readCard(str[i], str[i + 1]));

        if (this->_deck[(card.getRank() * 4) + card.getSuit()] == 0)
            throw std::runtime_error("Card already distributed.");
        this->_deck.reset((card.getRank() * 4) + card.getSuit());
        player.addCard(card);
    }

    // add board cards to the player
    player.addBoard(this->_board);
    return player;
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
            if (this->_board.count() > 0) continue;

            if (i + 1 < args.size())
                this->_parseBoard(args[i + 1]);
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
}

void TexasHoldem::play() {
    Player winner = this->winner();
}

Player TexasHoldem::winner() {
    Player winner;
    std::bitset<60> best;
    std::bitset<60> hand;
    std::bitset<60> bits_hand;
    std::bitset<60> bits_values;
    std::bitset<15> bits_count;
    std::vector<int> values;
    int score = 0;
    int max = -1;

    for (auto &player: this->_players) {
        hand = player.getHand();
        score = 0;

        // get indexes of the player's cards
        values.clear();
        for (std::size_t i = 0; i < hand.size(); i++)
            if (hand[i] == 1)
                values.push_back(i);

        // get all combinations and save the best hand
        for (const auto &combination: getCombinations(values, 5)) {
            bits_hand.reset();
            bits_count.reset();
            bits_values.reset();
            for (std::size_t i = 0; i < combination.size(); i++) {
                pushRankToBitset(bits_hand, (combination[i] - (combination[i] % 4)) / 4);
                pushRankToBitset(bits_count, (combination[i] - (combination[i] % 4)) / 4);
                bits_values.set(combination[i]);
            }

            score = this->_hand_rank.scores[player.handScore(bits_hand, bits_values, bits_count) - 1];
            if (player.getScore() <= score) {
                player.setScore(score);
                player.setBestHand(bits_values);
            }
        }

        if (player.getScore() > max) {
            max = player.getScore();
            best = player.getBestHand();
            winner = player;
        } else if (player.getScore() == max) {
            if (winner.tiesScore(winner.getBestHand()) < player.tiesScore(player.getBestHand())) {
                winner = player;
                best = player.getBestHand();
            } else if (winner.tiesScore(winner.getBestHand()) > player.tiesScore(player.getBestHand())) {
                continue;
            } else {
                std::cout << "tie" << std::endl;
            }
        }
    }

    return winner;
}
