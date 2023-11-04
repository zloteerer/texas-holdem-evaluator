#ifndef UTILS_HPP_
#define UTILS_HPP_

#define LENGTH_VALUES_BITSET 60
#define LENGTH_COUNT_BITSET 15
#define LENGTH_TIES_BITSET 20

#include <iostream>
#include <vector>

#include "Rank.hpp"
#include "Suit.hpp"

template <std::size_t T>
void print_bitset(std::bitset<T> bits) {
    bool leading_zeros = true;

    for (std::size_t i = 0; i < bits.to_string().size(); i++) {
        if (i % 4 == 0 && i != 0)
            std::cout << " ";
        if (i < T - 1 && bits.to_string()[i] == '0' && bits.to_string()[i + 1] != '0')
            std::cout << "0";
        else
            std::cout << bits.to_string()[i];
    }
    std::cout << std::endl;

    for (std::size_t i = T / 4 - 1; i > 1; i--) {
        std::cout << "♣♠♦♥ ";
    }
    std::cout << std::endl;

    for (std::size_t i = T / 4 - 1; i > 1; i--) {
        if (i < 10)
            std::cout << i;
        else if (i == 10)
            std::cout << "T";
        else if (i == 11)
            std::cout << "J";
        else if (i == 12)
            std::cout << "Q";
        else if (i == 13)
            std::cout << "K";
        else if (i == 14)
            std::cout << "A";
        std::cout << "    ";
    }
    std::cout << std::endl;
}

template <std::size_t T>
void print_player_hand(std::bitset<T> bits) {
    int suit = 0;
    for (std::size_t i = 0; i < bits.size(); i++) {
        if (bits[i] == 1) {
            suit = i % 4;
            std::cout << poker::rank_to_symbol_representation[(i - suit) / 4];
            std::cout << poker::suit_to_symbol_representation[suit];
        }
    }
    std::cout << std::endl;
}

template <std::size_t T>
void pushRankToBitset(std::bitset<T> &bits, int rank) {
    if (T == LENGTH_COUNT_BITSET) {
        bits.set(rank);
    } else if (T == LENGTH_VALUES_BITSET) {
        for (std::size_t i = 0; i < 4; i++) {
            if (i + 1 >= 4 && bits[rank * 4 + i] == 1)
                std::runtime_error("No more card of this rank");

            if (bits[rank * 4 + i] == 0) {
                bits.set(rank * 4 + i);
                break;
            }
        }
    }
}

template <std::size_t T>
void removeRankFromBitset(std::bitset<T> &bits, int rank) {
    if (T == LENGTH_COUNT_BITSET) {
        bits.remove(rank);
    } else if (T == LENGTH_VALUES_BITSET) {
        for (std::size_t i = 0; i < 4; i++) {
            if (i + 1 >= 4 && bits[rank * 4 + i] == 1)
                std::runtime_error("No more card of this rank");

            if (bits[rank * 4 + i] == 0) {
                bits.set(rank * 4 + i);
                break;
            }
        }
    }
}

void getCombinationsWithRecursion(
    const std::vector<int> values,
    int k,
    std::vector<std::vector<int>> &combinations,
    std::vector<int> &current,
    int index
);
std::vector<std::vector<int>> getCombinations(
    const std::vector<int> values,
    int k
);

#endif /* !UTILS_HPP_ */
