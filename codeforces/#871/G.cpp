#include <iostream>
#include <algorithm>

using ll = long long;;

const int N = 2025;

ll arr[N][N];

void init() {
    ll start_d = 1;
    for (int i = 1; i <= 2023; i++) {
        for (int j = 1; j <= i; j++) {
            arr[i][j] = arr[i][j - 1] + start_d * start_d;
            start_d++;
        }
    }
}

int main() {
    init();
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int f_n = 1;
        while ((f_n + 1) * f_n / 2 < n) f_n++;
        int f_m = n - (f_n - 1) * f_n / 2;

        int l = f_m, r = f_m;
        ll ans = 0;
        while (f_n) {
            ans += arr[f_n][r] - arr[f_n][l - 1];
            l = std::max(1, l - 1);
            r = std::min(f_n - 1, r);
            f_n--;
        }
        std::cout << ans << '\n';
    }
    return 0;
}