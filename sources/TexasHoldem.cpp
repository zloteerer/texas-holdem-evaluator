#include "TexasHoldem.hpp"

using poker::TexasHoldem;

TexasHoldem::TexasHoldem(int ac, char **av) {
    // set all bits to 1 except 8 first bits
    this->_deck.set();
    for (std::size_t i = 0; i < 8; i++)
        this->_deck.reset(i);

    this->_handle_arguments(ac, av);
}
TexasHoldem::~TexasHoldem() {
}

void TexasHoldem::_usage() {
    std::cout << "EDIT USAGE" << std::endl;
}

int TexasHoldem::_read_rank(char rank) {
    if (poker::rank_letters.count(rank) <= 0)
        throw std::runtime_error("Bad card entry.");
    return poker::rank_letters[rank];
}

int TexasHoldem::_read_suit(char suit) {
    if (poker::suit_letters.count(suit) <= 0)
        throw std::runtime_error("Bad card entry.");
    return poker::suit_letters[suit];
}

void TexasHoldem::_parse_board(std::string str) {
    int rank = 0;
    int suit = 0;

    // number of characters must be 6 or 8 or 10 (flop/turn/river)
    if (str.size() != 6 && str.size() != 8 && str.size() != 10)
        throw std::runtime_error("Board must have either 3, 4 or 5 cards.");

    for (std::size_t i = 0; i < str.size(); i += 2) {
        rank = this->_read_rank(str[i]);
        suit = this->_read_suit(str[i + 1]);

        if (this->_deck[(rank * 4) + suit] == 0)
            throw std::runtime_error("Card already distributed.");
        this->_deck.reset((rank * 4) + suit);
        this->_board.set((rank * 4) + suit);
    }
}

Player TexasHoldem::_parse_player(std::string str) {
    int rank = 0;
    int suit = 0;
    Player player(std::string("p" + std::to_string(this->_players.size() + 1)));

    // number of characters must be 4 (2 cards)
    if (str.size() != 4)
        throw std::runtime_error("A player must have 2 cards.");

    for (std::size_t i = 0; i < str.size(); i += 2) {
        rank = this->_read_rank(str[i]);
        suit = this->_read_suit(str[i + 1]);

        if (this->_deck[(rank * 4) + suit] == 0)
            throw std::runtime_error("Card already distributed.");
        this->_deck.reset((rank * 4) + suit);
        player.addCard(rank, suit);
    }

    // add board cards to the player
    player.addBoard(this->_board);
    return player;
}

void TexasHoldem::_handle_arguments(int ac, char **av) {
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
                this->_parse_board(args[i + 1]);
            else
                throw std::runtime_error("Not enough arguments. Try --help or -h.");

            // it allows to jump the cards
            i += 1;
        } else if (compare("--player", args[i]) || compare("-p", args[i])) {
            if (i + 1 < args.size())
                this->_players.push_back(this->_parse_player(args[i + 1]));
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
    std::vector<Player> winner = this->winner();

    if (winner.size() == 1) {
        std::cout << winner.at(0).getName() << ": " << poker::hand_rank_to_representation[winner.at(0).getScore()] << std::endl;
        print_bitset(winner.at(0).getBestHand());
        print_player_hand(winner.at(0).getBestHand());
    } else if (winner.size() > 1) {
        std::cout << "Tie!" << std::endl;
        for (const auto &player: winner) {
            std::cout << player.getName() << ": " << poker::hand_rank_to_representation[winner.at(0).getScore()] << std::endl;
            print_bitset(player.getBestHand());
            print_player_hand(player.getBestHand());
        }
    }
}

std::vector<Player> TexasHoldem::winner() {
    std::vector<Player> winner;
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

            score = poker::hand_rank_scores[player.handScore(bits_hand, bits_values, bits_count) - 1];
            if (player.getScore() <= score) {
                player.setScore(score);
                player.setBestHand(bits_values);
            }
        }

        if (player.getScore() > max) {
            max = player.getScore();
            if (winner.size() > 0) {
                winner.clear();
                winner.push_back(player);
            } else {
                winner.push_back(player);
            }
        } else if (player.getScore() == max) {
            if (winner.at(0).tiesScore(winner.at(0).getBestHand()) < player.tiesScore(player.getBestHand())) {
                winner.clear();
                winner.push_back(player);
            } else if (winner.at(0).tiesScore(winner.at(0).getBestHand()) > player.tiesScore(player.getBestHand())) {
                continue;
            } else {
                winner.push_back(player);
            }
        }
    }

    return winner;
}
