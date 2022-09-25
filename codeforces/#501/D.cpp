#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
std::vector<ll> ans;

int main() {
    ll n, k, s;
    std::cin >> n >> k >> s;
    if ((n - 1) * k < s || k > s) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        ll x = s / k;
        ll mod = s % k;
        ll last = 1;
        for (ll i = 1; i <= mod; i++) {
            if (last == 1) {
                last = last + x + 1;
            } else {
                last = last - x - 1;
            }
            std::cout << last << ' ';
        }
        if (last != 1) {
            x = -x;
        }
        for (ll i = mod + 1; i <= k; i++) {
            last = last + x;
            x = -x;
            std::cout << last << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}