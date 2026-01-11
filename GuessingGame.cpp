#include <random>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <charconv>

void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());

    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);
    std::string guess;
    while (true) {
        int magic_number = dist(gen);
        std::cout << "I am thinking of a number 1-100. Take a guess or type 'Q' to quit: ";
        std::getline(std::cin, guess);
        while (true) {
            trim(guess);
            if (guess.size() == 1 && (guess[0] == 'q' || guess[0] == 'Q')) {
                std::cout << "Exiting fizzbuzz" << std::endl;
                return 0;
            } else if (guess.find(' ') != std::string::npos || guess.find('\t') != std::string::npos) {
                std::cout << "Can only accept one argument at a time! Guess again: ";
                std::getline(std::cin, guess);
            } else if (!std::all_of(guess.begin(), guess.end(), [](unsigned char c) {
                return std::isdigit(c);
            })) {
                std::cout << "Input must be an integer! Guess again: ";
                std::getline(std::cin, guess);
            } else {
                int num_guess;
                std::from_chars(guess.data(), guess.data() + guess.size(), num_guess);
                if (num_guess < 1 || num_guess > 100) {
                    std::cout << "The magic number is between 1 & 100! Guess again: ";
                    std::getline(std::cin, guess);
                } else if (magic_number != num_guess) {
                    std::cout << "Not quite! Guess again: ";
                    std::getline(std::cin, guess);
                } else {
                    std::cout << "You got it! Let's play again." << std::endl;
                    break;
                }
            }
        }
    }
}