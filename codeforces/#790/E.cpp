#include <iostream>
#include <algorithm>

#define N 200005

int d[N], sum[N];

int main() {
    int t, n, q;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            std::cin >> d[i];
        }
        std::sort(d + 1, d + n + 1);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + d[n - i + 1];
        }
        int x;
        while (q--) {
            std::cin >> x;
            int p = std::lower_bound(sum + 1, sum + 1 + n, x) - sum;
            std::cout << ((p >= 1 && p <= n) ? p : -1) << '\n';
        }
    }
    return 0;
}