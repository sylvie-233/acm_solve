#include <iostream>
#include <string>
#include <cctype>

int main() {
    int t;
    std::string s;
    std::cin >> t;
    while (t--) {
        std::cin >> s;
        if (std::tolower(s[0]) == 'y'
            && std::tolower(s[1]) == 'e'
            && std::tolower(s[2]) == 's') {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
    }
    return 0;
}