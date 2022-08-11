#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int dp[2005][2005];
bool rained[2005];
int w[2005], pos[2005], w2[2005];

int main() {
    int a, n, m;
    std::cin >> a >> n >> m;
    for (int i = 1; i <= n; i++) {
        int l, r;
        std::cin >> l >> r;
        for (int j = l + 1; j <= r; j++) {
            rained[j] = true;
        }
    }
    for (int i = 1; i <= m; i++) {
        int x, p;
        std::cin >> x >> p;
        w2[i] = p;
        if (!w[x]) {
            w[x] = p;
            pos[x] = i;
        } else {
            if (p < w[x]) {
                w[x] = p;
                pos[x] = i;
            }
        }
    }
    // std::memset(dp, -1, sizeof(dp));
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= m; j++) {
            if (!i) {
                break;
            }
            if (!rained[i]) {
                if (!j) {
                    int mn = -1;
                    for (int k = 0; k <= m; k++) {
                        if (dp[i - 1][k] != -1) {
                            if (mn == -1) {
                                mn = dp[i - 1][k];
                            } else {
                                mn = std::min(mn, dp[i - 1][k]);
                            }
                        }
                    }
                    dp[i][0] = mn;
                } else {
                    if (dp[i - 1][j] != -1) {
                        dp[i][j] = dp[i - 1][j] + w2[j];
                    }
                }
            } else {
                if (j) {
                    if (dp[i - 1][j] != -1) {
                        dp[i][j] = dp[i - 1][j] + w2[j];
                    }
                }
            }
        }
        if (w[i] != 0) {
            int mn = -1;
            for (int j = 0; j <= m; j++) {
                if (j != pos[i] && dp[i][j] != -1) {
                    if (mn == -1) {
                        mn = dp[i][j];
                    } else {
                        mn = std::min(mn, dp[i][j]);
                    }
                }
            }
            if (mn != -1) {
                dp[i][pos[i]] = mn;
            }
        }
    }
    int ans = -1;
    for (int i = 0; i <= m; i++) {
        if (dp[a][i] != -1) {
            if (ans == -1) {
                ans = dp[a][i];
            } else {
                ans = std::min(ans, dp[a][i]);
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}