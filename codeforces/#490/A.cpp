#include <iostream>

int a[105];

int main() {
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    int ans = 0, p = 1;
    while (p <= n && a[p] <= k) {
        ans++;
        p++;
    }
    int p2 = n;
    while (p2 > p && a[p2] <= k) {
        ans++;
        p2--;
    }
    std::cout << ans << '\n';
    return 0;
}