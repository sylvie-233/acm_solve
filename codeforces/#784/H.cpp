#include <iostream>
#include <cstring>

int cnt[32];

int main() {
    int t, n, k, a;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        std::memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            std::cin >> a;
            for (int j = 30; j >= 0; j--) {
                cnt[j] += (a >> j) & 1;
            }
        }

        for (int i = 30; i >= 0; i--) {
            if (cnt[i] < n) {
                if (cnt[i] + k >= n) {
                    k -= n - cnt[i];
                    cnt[i] = n;
                }
            }
        }
        int ans = 0;
        for (int i = 30; i >= 0; i--) {
            if (cnt[i] >= n) {
                ans |= (1 << i);
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}