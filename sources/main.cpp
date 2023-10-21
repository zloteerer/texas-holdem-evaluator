#include <exception>
#include <chrono>
#include "TexasHoldem.hpp"

int main(int ac, char **av) {
    try {
        poker::TexasHoldem game(ac, av);

        game.play();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
