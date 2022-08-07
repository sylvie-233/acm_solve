#include <iostream>
#include <string>

int main() {
    int t, n;
    std::string s;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> s;
        int cnt = 0;
        bool f = true;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'W') {
                if (cnt >= 1) {
                    int p = i - cnt;
                    while (p < i) {
                        if (s[p] != s[i - 1]) {
                            break;
                        }
                        p++;
                    }
                    if (p == i) {
                        f = false;
                        cnt = 0;
                        break;
                    }
                } 
                cnt = 0;
                continue;
            } 
            cnt++;
        }
        if (cnt >= 1) {
            int p = n - cnt;
            while (p < n) {
                if (s[p] != s[n - 1]) {
                    break;
                }
                p++;
            }
            if (p == n) {
                f = false;
                cnt = 0;
            }
        } 
        std::cout << (f ? "YES" : "NO") << '\n';
    }
    return 0;
}