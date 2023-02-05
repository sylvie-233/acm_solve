#include <iostream>
#include <string>

int main() {
    int t, n;
    std::string s, s_t;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> s_t >> s;
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if ((s_t[i] == 'R' || s[i] == 'R') && s_t[i] != s[i]) {
                flag = false;
                break;
            }
        }
        std::cout << (flag ? "YES\n" : "NO\n");
    }
    return 0;
}