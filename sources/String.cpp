#include "String.hpp"

bool compare(std::string s1, std::string s2) {
    return ((s1.compare(s2) < 0 || s1.compare(s2)) > 0 ? false : true);
}