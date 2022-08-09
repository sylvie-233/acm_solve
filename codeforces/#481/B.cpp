#include <iostream>
#include <string>

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'x') {
            cnt++;
        } else {
            if (cnt >= 3) {
                ans += cnt - 2;
            }
            cnt = 0;
        }
    }
    if (cnt >= 3) {
        ans += cnt - 2;
    }
    std::cout << ans << '\n';
    return 0;
}