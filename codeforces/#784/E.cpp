#include <iostream>
#include <cstring>
#include <string>

typedef long long ll;

int c1[11][11], c2[11][11];

int main() {
    int t, n;
    std::string s;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                c1[i][j] = c2[i][j] = 0;
            }
        }
        // std::memset(c1, 0, sizeof(c1));
        // std::memset(c2, 0, sizeof(c2));
        ll ans = 0;
        while (n--) {
            std::cin >> s;
            for (int i = 0; i < 11; i++) {
                if (i != (s[1] - 'a')) {
                    ans += c1[s[0] - 'a'][i];
                }
            }
            for (int i = 0; i < 11; i++) {
                if (i != (s[0] - 'a')) {
                    ans += c2[s[1] - 'a'][i];
                }
            }
            c1[s[0] - 'a'][s[1] - 'a']++;
            c2[s[1] - 'a'][s[0] - 'a']++;
            // std::cout << ans << '\n';
        }
        std::cout << ans << '\n';
    }
    return 0;
}