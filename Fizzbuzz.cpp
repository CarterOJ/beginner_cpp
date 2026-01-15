#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <sstream>
#include <charconv>

std::string fizzbuzz(long long n) {
    std::ostringstream oss;
    if (n == 0) {
        return "\n";
    }
    for (long long i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            oss << "FizzBuzz\n";
        } else if (i % 3 == 0) {
            oss << "Fizz\n";
        } else if (i % 5 == 0) {
            oss << "Buzz\n";
        } else {
            oss << i << "\n";
        }
    }
    return oss.str();
}

void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());

    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
}

int main() {
    while (true) {
        std::string iters;
        std::cout << "Please enter the iteration amount to fizzbuzz. Type 'Q' to quit: ";
        std::getline(std::cin, iters);
        trim(iters);
        if (iters.size() == 1 && (iters[0] == 'q' || iters[0] == 'Q')) {
            std::cout << "Exiting fizzbuzz" << std::endl;
            break;
        } else if (iters.find(' ') != std::string::npos || iters.find('\t') != std::string::npos) {
            std::cout << "Can only accept one argument!" << std::endl;
        } else if (!std::all_of(iters.begin(), iters.end(), [](unsigned char c) {
            return std::isdigit(c);
        })) {
            std::cout << "Input must be a positive integer!" << std::endl;
        } else {
            long long num;
            std::from_chars(iters.data(), iters.data() + iters.size(), num);
            std::cout << fizzbuzz(num);
        } 
    }
}