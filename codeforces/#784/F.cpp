#include <iostream>
#include <algorithm>

int w[200005], sum1[200005], sum2[200005];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::cin >> w[i];
        }
        sum1[0] = w[0];
        sum2[0] = w[n - 1];
        for (int i = 1; i < n; i++) {
            sum1[i] = sum1[i - 1] + w[i];
            sum2[i] = sum2[i - 1] + w[n - 1 - i];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (std::binary_search(sum2, sum2 + n - 1 - i, sum1[i])) {
                int cnt = std::lower_bound(sum2, sum2 + n - 1 - i, sum1[i]) - sum2 + 1;
                ans = std::max(ans, i + 1 + cnt);
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}