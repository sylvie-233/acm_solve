#include <iostream>
#include <cstring>
#include <algorithm>

#define N 100005

int a[N], n;

int dfs(int i, int op, int d, int cnt) {
    if (i == n) {
        return cnt;
    }
    if ((a[i] - (a[i - 1] + op)) == d) {
        return dfs(i + 1, 0, d, cnt);
    }
    if ((a[i] + 1 - (a[i - 1] + op)) == d) {
        return dfs(i + 1, 1, d, cnt + 1);
    }
    if ((a[i] - 1 - (a[i - 1] + op)) == d) {
        return dfs(i + 1, -1, d, cnt + 1);
    }
    return -1;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    if (n == 1 || n == 2) {
        std::cout << 0 << '\n';
    } else {
        int ans = -1, d = a[1] - a[0];
        int t;

        t = dfs(2, -1, d, 2);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, -1, d - 1, 1);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, -1, d - 2, 2);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }

        t = dfs(2, 0, d + 1, 1);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, 0, d, 0);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, 0, d - 1, 1);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }

        t = dfs(2, 1, d + 2, 2);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, 1, d + 1, 1);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }
        t = dfs(2, 1, d, 2);
        if (t != -1) {
            if (ans == -1) {
                ans = t;
            } else {
                ans = std::min(ans, t);
            }
        }

        std::cout << ans << '\n';
    }
    
    return 0;
}