// decipher.cpp by TianhaoLee 20101110201
#include <iostream>
#include <string>
#include <algorithm>

std::string vigenere_decrypt(const std::string &ciphertext, const std::string &key) {
    std::string plaintext {};
    for (int i = 0; i < ciphertext.size(); ++i) {
        plaintext += (ciphertext[i] - key[i % key.size()] + 26) % 26 + 'A';
    }
    return plaintext;
}

int main(int argc, const char **argv) {
    std::string origin {}; 
    std::cout << "Input vigenere ciphertext: "; 
    std::cin >> origin; 

    std::string key {}; 
    std::cout << "Input key: "; 
    std::cin >> key; 

    std::transform(origin.begin(), origin.end(), 
                   origin.begin(), [](unsigned char c){ return std::tolower(c); });
    std::transform(key.begin(), key.end(), 
                   key.begin(), [](unsigned char c){ return std::tolower(c); });

    std::cout << vigenere_decrypt(origin, key) << std::endl; 

    return 0; 
}