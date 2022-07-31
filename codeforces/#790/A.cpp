#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::string s;
        std::cin >> s;
        int a = 0, b = 0;
        for (int i = 0; i < 3; i++) {
            a += s[i] - '0';
        }
        for (int i = 3; i < 6; i++) {
            b += s[i] - '0';
        }
        std::cout << (a == b ? "YES" : "NO") << '\n';
    }
    return 0;
}