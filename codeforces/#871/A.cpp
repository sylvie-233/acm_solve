#include <iostream>
#include <string>

int main() {
    int t;
    std::string str = "codeforces", s;
    std::cin >> t;
    while (t--) {
        std::cin >> s;
        int ans = 0;
        for (int i = 0; i < str.length(); i++) {
            if (s[i] != str[i]) ans++;
        }
        std::cout << ans << '\n';
    }
    return 0;
}