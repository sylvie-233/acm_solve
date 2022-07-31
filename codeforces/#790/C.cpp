#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>

#define INF 0x3f3f3f3f

std::string s[55];
int d[55][10];

int main() {
    int t, n, m;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        for (int i = 0; i < n; i++) {
            std::cin >> s[i];
        }
        std::memset(d[0], 0, (m + 1) * sizeof(int));
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                d[i][j] = s[i][j] - s[0][j];
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int sum = 0;
                for (int k = 0; k < m; k++) {
                    sum += std::abs(d[i][k] - d[j][k]);
                }
                ans = std::min(ans, sum);
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}