#include <iostream>
#include <algorithm>

#define N 200005

typedef long long ll;

ll a[N], sum[N];

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum[i] = a[i] + sum[i - 1];
    }
    while (m--) {
        ll t;
        std::cin >> t;
        int p = std::lower_bound(sum + 1, sum + 1 + n, t) - sum - 1;
        ll p2 = t - sum[p];
        std::cout << p + 1 << ' ' << p2 << '\n';
    }
    return 0;
}