#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

#define N 200005

std::map<int, int> mp;
int dp[N], a[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        dp[i] = 1;
        if (mp[a[i] - 1]) {
            dp[i] = std::max(dp[i], dp[mp[a[i] - 1]] + 1);
        }
        mp[a[i]] = i;
    }
    int p = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
            p = i;
        }
    }
    std::vector<int> vec;
    vec.push_back(p);
    int t = a[p] - 1, cnt = ans - 1;
    for (int i = p - 1; i > 0; i--) {
        if (!cnt) {
            break;
        }
        if (a[i] == t) {
            t--;
            cnt--;
            vec.push_back(i);
        }
    }
    // std::cout << p << ' ' << ans << '\n';
    std::cout << ans << '\n';
    for (int i = vec.size() - 1; i >= 0 ; i--) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}

