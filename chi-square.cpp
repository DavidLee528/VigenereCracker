// chi-square.cpp by TianhaoLee 20101110201
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

double chi_square(const std::vector<char> &vec, size_t key) {
    std::vector<int> freq(26);
    for (char c : vec) {
        if (isalpha(c)) {
            c = tolower(c);
            c = (c - 'a' + (26 - key)) % 26 + 'a';
            freq[c - 'a']++;
        }
    }
    std::cout << "\t"; 

    // The expected frequency of each letter in English text is taken from Wikipedia.
    // https://en.wikipedia.org/wiki/Letter_frequency
    const std::vector<double> expected_freq = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
                                               0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                                               0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
                                               0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                                               0.02758, 0.00978, 0.02360, 0.00150, 0.01974,
                                               0.00074};
    // ensure that summation of expected_freq is 1.0
    double sum {0.0}; 
    for (const auto & each : expected_freq) sum += each; 
    assert(std::abs(1.0 - sum) < 1e-4); 

    int n = vec.size();
    double chi_square = 0;
    for (int i = 0; i < freq.size(); i++) {
        double observed_freq = static_cast<double>(freq[i]) / n;
        chi_square += pow(observed_freq - expected_freq[i], 2) / expected_freq[i];
    }

    return chi_square;
}

int main(int argc, const char **argv) {
    std::string origin {}; 
    std::cout << "Input vigenere ciphertext: "; 
    std::cin >> origin; 

    size_t period {}; 
    std::cout << "Input possible key period (minimum): "; 
    std::cin >> period; 

    // ensure that origin.length() will not make var i overflow
    assert(origin.length() < std::numeric_limits<size_t>::max()); 

    std::string possible_key {""}; 

    std::cout << std::endl; 

    // do period time of caeser decipher
    for (size_t i = 0; i < period; ++i) {
        std::cout << "=======================================================" << std::endl; 
        std::cout << "In the Caeser cipher crack number " << i + 1 << "#: " << std::endl << std::endl; 
        std::cout << "Number" << "\t\tLetter" << "\t\tChi-Square" << std::endl; 
        
        // generate work vector for each caeser decipher
        std::vector<char> vec {}; 
        for (size_t j = i; j < origin.length(); j += period) {
            vec.push_back(origin.at(j)); 
        }

        // exhaust all possible key which need only 26 tries
        char pos {'a'}; 
        std::vector<std::pair<char, double>> possibility_array {};
        for (size_t j = 0; j < 26; ++j) {
            double curr_chi_square = chi_square(vec, j); 
            possibility_array.push_back(std::make_pair(pos, curr_chi_square)); 
            std::cout << j << "\t" << pos++ << "\t"; 
            std::cout << "\t" << curr_chi_square << std::endl; 
        }

        // sort from most possible to less possible
        // namely ascending sort of chi-square
        std::sort(possibility_array.begin(), possibility_array.end(), 
        [](const std::pair<char, double> &lhs, const std::pair<char, double> &rhs) {
            return lhs.second < rhs.second; 
        }); 

        std::cout << std::endl; 
        std::cout << "The " << i + 1 << "# digit of key (descending order by possibility): " << std::endl; 
        for (const auto & ch : possibility_array) std::cout << ch.first << " "; 
        possible_key += possibility_array.at(0).first; 

        std::cout << std::endl << "=======================================================" << std::endl; 
        std::cout << std::endl << std::endl; // begin next round
    }

    std::cout << std::endl << "Possible key: " << possible_key << std::endl; 

    return 0; 
}