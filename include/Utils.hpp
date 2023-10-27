#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <vector>

template <std::size_t T>
void debug_bitset(std::bitset<T> bits, std::string name) {
    std::cout << "bitset<" << T << ">: " << name << std::endl;
    for (std::size_t i = 0; i < bits.to_string().size(); i++) {
        if (i % 4 == 0)
            std::cout << " ";
        std::cout << bits.to_string()[i];
    }
    std::cout << std::endl;
    std::cout << " ";
    for (std::size_t i = T / 4 - 1; i > 1; i--) {
        std::cout << "♣♠♦♥ ";
    }
    std::cout << std::endl;
    std::cout << " ";
    for (std::size_t i = T / 4 - 1; i > 1; i--) {
        std::cout << i;
        if (i >= 10)
            std::cout << "   ";
        else
            std::cout << "    ";
    }
    std::cout << std::endl << std::endl;
}

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
