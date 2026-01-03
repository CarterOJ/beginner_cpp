#include <string>
#include <algorithm>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <cctype>
#include <sstream>

std::string fizzbuzz(boost::multiprecision::cpp_int n) {
    std::ostringstream oss;
    if (n == 0) {
        return "\n";
    }
    for (boost::multiprecision::cpp_int i = 1; i <= n; i++) {
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
        std::string line;
        std::cout << "Please enter the iteration amount to fizzbuzz. Type 'Q' to quit: ";
        std::getline(std::cin, line);
        trim(line);
        if (line.size() == 1 && (line[0] == 'q' || line[0] == 'Q')) {
            std::cout << "Exiting fizzbuzz" << std::endl;
            break;
        } else if (line.find(' ') != std::string::npos || line.find('\t') != std::string::npos) {
            std::cout << "Can only accept one argument!" << std::endl;
        } else if (!std::all_of(line.begin(), line.end(), [](unsigned char c) {
            return std::isdigit(c);
        })) {
            std::cout << "Input must be a positive integer!" << std::endl;
        } else {
            boost::multiprecision::cpp_int num(line);
            std::cout << fizzbuzz(num);
        } 
    }
}