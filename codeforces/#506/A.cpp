#include <iostream>
#include <string>

int main() {
    int n, k;
    std::string t;
    std::cin >> n >> k >> t;
    int p = -1;
    for (int i = 1; i < n; i++) {
        int j = i, j2 = 0;
        while (t[j] == t[j2] && j < n && j2 < n) {
            j++;
            j2++;
        }
        if (j == n) {
            p = i;
            break;
        }
    }
    // std::cout << p << '\n';
    // std::cout << t.substr(n - p) << '\n';
    std::string ans = t;
    for (int i = 1; i < k; i++) {
        ans += (p == -1 ? t : t.substr(n - p));
    }
    std::cout << ans << '\n';
    return 0;
}