#include <iostream>
#include <algorithm>

#define N 1005

int d[N];

int main() {
    int n, w;
    std::cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i];
    }
    int sum = 0, l = 0, r = w;
    for (int i = 1; i <= n; i++) {
        sum += d[i];
        l = std::max(l, 0 - sum);
        r = std::min(r, w - sum);
        if (l > r) {
            break;
        }
    }
    int ans = 0;
    if (l <= r) {
        ans = r - l + 1;
    }
    // std::cout << l << ' ' << r << '\n';
    std::cout << ans << '\n';
    return 0;
}