#include "Utils.hpp"

void getCombinationsWithRecursion(
    const std::vector<int> values,
    int k,
    std::vector<std::vector<int>> &combinations,
    std::vector<int> &current,
    int index
) {
    if (k == 0) {
        combinations.push_back(current);
        return;
    }

    for (int i = index; i < values.size(); ++i) {
        current.push_back(values[i]);
        getCombinationsWithRecursion(values, k - 1, combinations, current, i + 1);
        current.pop_back();
    }
}

std::vector<std::vector<int>> getCombinations(
    const std::vector<int> values,
    int k
) {
    std::vector<std::vector<int>> combinations;
    std::vector<int> current;

    getCombinationsWithRecursion(values, k, combinations, current, 0);
    return combinations;
}

void print_player_hand(std::bitset<60> bits) {
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