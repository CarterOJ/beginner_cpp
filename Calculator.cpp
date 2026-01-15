#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <vector>
#include <format>

long double binary_operation(long double op_one, long double op_two, std::string op) {
    if (op == "+") {
        return op_one + op_two;
    } else if (op == "-") {
        return op_one - op_two;
    } else if (op == "*") {
        return op_one * op_two;
    } else {
        return op_one / op_two;
    }
}

void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());

    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
}

int main() {
    std::cout << "To use the calculator, please adhere to the following format: [int] '+'||'-'||'*'||'/' [int]." << std::endl;
    std::string user_in;
    while (true) {
        std::cout << "Enter an expression or type 'Q' to quit: " << std::endl;
        std::getline(std::cin, user_in);
        trim(user_in);
        if (user_in.size() == 1 && (user_in[0] == 'q' || user_in[0] == 'Q')) {
            std::cout << "Exiting calculator" << std::endl;
            break;
        }
        user_in.erase(
            std::remove(user_in.begin(), user_in.end(), ' '),
            user_in.end()
        );
        std::regex pattern(R"(-?(?:\d*\.\w+|\w+(?:\.\w+)?|\.\w+)|[-+*/])");
        std::vector<std::string> params;
        auto begin = std::sregex_iterator(user_in.begin(), user_in.end(), pattern);
        auto end   = std::sregex_iterator();
        bool found_operator = false;
        for (auto it = begin; it != end; ++it) {
            if (std::regex_match(it->str(), std::regex(R"(^[-+*/]$)"))) {
                found_operator = true;
                params.push_back(it->str());
            } else if (found_operator == false && std::regex_match(it->str(), std::regex(R"(^-.*$)"))) {
                found_operator = true;
                params.push_back(it->str().substr(0, 1));
                params.push_back(it->str().substr(1));
            } else {
                params.push_back(it->str());
            }
        }
        if (params.size() != 3) {
            std::cout << "There must be exactly three arguments!" << std::endl;
        } else if (!std::regex_match(params.at(0), std::regex(R"(-?\d+)"))) {
            std::cout << std::format("{} is not an integer!", params.at(0)) << std::endl;
        } else if (!std::regex_match(params.at(2), std::regex(R"(-?\d+)"))) {
            std::cout << std::format("{} is not an integer!", params.at(2)) << std::endl;
        } else if (!std::regex_match(params.at(1), std::regex(R"([-+*/])"))) {
            std::cout << std::format("{} is not a valid operator!", params.at(1)) << std::endl;
        } else {
            long double op_one;
            long double op_two;
            std::from_chars(params.at(0).data(), params.at(0).data() + params.at(0).size(), op_one);
            std::from_chars(params.at(2).data(), params.at(2).data() + params.at(2).size(), op_two);
            if (op_two == 0 && params.at(1) == "/") {
                std::cout << "Undefined" << std::endl;
            } else {
                long double result = binary_operation(op_one, op_two, params.at(1));
                std::cout << std::format("Result: {}", result) << std::endl;
            }
        }
    }
}