#include <string>
#include <iostream>
#include <cctype>

bool check_palindrome(std::string pal) {
    if (pal.size() <= 1) {
        return true;
    } else if (pal.at(0) == pal.at(pal.size() - 1)) {
        return check_palindrome(pal.substr(1, pal.size() - 2));
    }
    return false;
}

void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());

    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
}

int main() {
    std::string palindrome;
    while (true) {
        std::cout << "Enter any string to check if it's a palindrome. Type 'Q' to exit: ";
        std::getline(std::cin, palindrome);
        trim(palindrome);
        if (palindrome.size() == 1 && (palindrome[0] == 'q' || palindrome[0] == 'Q')) {
            std::cout << "Exiting palindrome checker" << std::endl;
            break;
        }
        std::cout << (check_palindrome(palindrome) ? "true" : "false") << std::endl;
    }
}