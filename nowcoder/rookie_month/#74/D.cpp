#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

std::vector<ll> vec;

int main() {
    int t, n, m;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        ll sum = 0, a, max_suf = 0;
        vec.clear();
        for (int i = 1; i <= n; i++) {
            std::cin >> a;
            sum += a;
            if (a > 0) vec.push_back(a * (n - i + 1));
        }
        ll res = 0;
        std::sort(vec.rbegin(), vec.rend());
        for (int i = 0; i < vec.size() && i < m; i++) {
            res += vec[i];
        }
        std::cout << sum - res << '\n';
    }
    return 0;
}