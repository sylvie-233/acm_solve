#include <iostream>
#include <cmath>
#include <algorithm>

using ll = long long;

// const int N = 2e5 + 5;
// ll arr[N];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        ll ans = 0, a;
        int cnt = 0, flag = 0;
        for (int i = 1; i <= n; i++) {
            std::cin >> a;
            ans += std::abs(a);
            if (a < 0) {
                flag = -1;
            } else if (a > 0) {
                if (flag == -1) {
                    cnt++;
                    flag = 0;
                }
            }
        }
        if (flag == -1) cnt++;
        std::cout << ans << ' ' << cnt << '\n';
    }
    return 0;
}