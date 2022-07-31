#include <iostream>
#include <algorithm>
#include <map>

int d[205][205];
std::map<int, int> mp1, mp2;

int main() {
    int t, n, m;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        mp1.clear();
        mp2.clear();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cin >> d[i][j];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int sum = 0, x, y;
                x = i - 1;
                y = j - 1;
                while (x >= 1 && y >= 1) {
                    sum += d[x][y];
                    x--;
                    y--;
                }

                x = i - 1;
                y = j + 1;
                while (x >= 1 && y <= m) {
                    sum += d[x][y];
                    x--;
                    y++;
                }

                x = i + 1;
                y = j - 1;
                while (x <= n && y >= 1) {
                    sum += d[x][y];
                    x++;
                    y--;
                }

                x = i + 1;
                y = j + 1;
                while (x <= n && y <= m) {
                    sum += d[x][y];
                    x++;
                    y++;
                }

                sum += d[i][j];
                // std::cout << i << "=========" << j << "=========" << sum << '\n';
                ans = std::max(ans, sum);
            }
        }
        std::cout << ans << '\n';
    }
    

    return 0;
}