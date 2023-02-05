#include <algorithm>
#include <string>
#include <iostream>

int main() {
    int t, n;
    std::string s_t = "Timru", s;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> s;
        if (n != 5) {
            std::cout << "NO\n";
            continue;
        }
        std::sort(s.begin(), s.end());
        if (s != s_t) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
        }
    }
    return 0;
}