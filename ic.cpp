// ic.cpp by TianhaoLee 20101110201
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <limits>

double index_of_coincidence(const std::vector<char> &ciphertext) {
    std::vector<int> freq(26);
    int n = 0;

    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            ++freq[std::tolower(c) - 'a'];
            ++n;
        }
    }

    double sum = 0;
    for (int f : freq) {
        sum += f * (f - 1);
    }

    return sum / (n * (n - 1));
}

double avg_ic(const std::string &origin, size_t period) {
    std::vector<std::vector<char>> vec {}; 
    vec.resize(period); 

    // ensure that origin.length() will not make var i overflow
    assert(origin.length() < std::numeric_limits<size_t>::max()); 

    for (size_t i = 0; i < origin.length(); ++i) {
        vec.at(i % period).push_back(origin.at(i)); 
    }

    double avg_ic {0.0}; 
    for (size_t i = 0; i < period; ++i) {
        avg_ic += index_of_coincidence(vec.at(i)); 
    }

    return avg_ic / period; 
}

int main(int argc, const char **argv) {
    std::string origin {}; 
    std::cout << "Input vigenere ciphertext: "; 
    std::cin >> origin; 

    size_t period_limit {}; 
    std::cout << "Input period limit:"; 
    std::cin >> period_limit; 

    std::cout << std::endl << "period" << "\tindex of coincidence" << std::endl; 
    for (size_t i = 1; i <= period_limit; ++i) {
        std::cout << i << "\t" << avg_ic(origin, i) << std::endl; 
    }

    return 0; 
}