#include <iostream>

using ll = long long;

int main() {
    int t;
    ll a;
    std::cin >> t;
    while (t--) {
        std::cin >> a;
        ll ans = 0;
        while (a) {
            ans += a;
            a >>= 1;
        }
        std::cout << ans << '\n';
    }
    return 0;
}