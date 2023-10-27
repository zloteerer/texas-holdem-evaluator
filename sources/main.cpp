#include <exception>
#include <chrono>
#include "TexasHoldem.hpp"

int main(int ac, char **av) {
    // MonteCarloTreeSearch mcts;
    try {
        poker::TexasHoldem game(ac, av);

        game.play();
        // mcts.simulate();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
