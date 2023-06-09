#include <iostream>

int main() {
    int t;
    std::cin >> t;
    if (t % 2 == 0 || t % 3 == 0 || t % 5 == 0 || t % 7 == 0) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}