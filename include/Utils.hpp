#ifndef UTILS_HPP_
#define UTILS_HPP_

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
void print_player_hand(std::bitset<60> bits);

template <std::size_t T>
void pushRankToBitset(std::bitset<T> &bits, int rank) {
    if (T == 15) {
        bits.set(rank);
    } else if (T == 60) {
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
    if (T == 15) {
        bits.remove(rank);
    } else if (T == 60) {
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
