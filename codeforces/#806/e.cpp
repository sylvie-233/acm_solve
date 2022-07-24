#include <iostream>

char a[105][105];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> a[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == '1') {
                    int cnt = 0;
                    if (a[j][n - 1 - i] != '1') {                     
                        cnt++;
                    }
                    if (a[n - 1 - i][n - 1 - j] != '1') {
                        cnt++;
                    }
                    if (a[n - 1 - j][i] != '1') {
                        cnt++;
                    }
                    if (cnt == 3) {
                        a[i][j] = '0';
                        ans += 1;
                    } else {
                        a[j][n - 1 - i] = a[n - 1 - i][n - 1 -j] = a[n - 1 - j][i] = '1';
                        ans += cnt;
                    }
                    // std::cout << "--" << cnt << "--\n";
                    // std::cout << "--" << i << "---" << j << "--\n";
                    // std::cout << "--" << ans << "--\n";
                }
            }
        }
        std::cout << ans << '\n';
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         std::cout << a[i][j];
        //     }
        //     std::cout << '\n';
        // }
    }
    return 0;
}