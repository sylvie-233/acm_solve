#include <iostream>
#include <algorithm>
#include <cstring>

#define N 200005

int a[N], l[N], r[N];

int main() {
    int t, n, s, sum;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> s;
        std::memset(l, 0, n * sizeof(int));
        std::memset(r, 0, n * sizeof(int));
        sum = 0;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            sum += a[i];
            if (a[i]) {
                l[sum] = i + 1;
            }
        }
        sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            sum += a[i];
            if (a[i]) {
                r[sum] = n - i;
            }
        }
        // for (int i = 0; i <= sum; i++) {
        //     std::cout << l[i] << ' ';
        // }
        // std::cout << std::endl;
        // for (int i = 0; i <= sum; i++) {
        //     std::cout << r[i] << ' ';
        // }
        // std::cout << std::endl;
        if (s > sum) {
            std::cout << -1 << std::endl;
        } else if (s == sum) {
            std::cout << 0 << std::endl;
        } else {
            int res = n;
            for (int i = 1; i <= sum - s; i++) {
                res = std::min(l[i] + r[sum - s - i], std::min(r[i] + l[sum - s -i], res));
            }
            std::cout << res << std::endl;
        }
    }
    return 0;
}