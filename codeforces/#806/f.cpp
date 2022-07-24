#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

typedef long long ll;

std::vector<ll> vec_i;
std::vector<std::pair<ll, ll>> vec_a;

int main() {
    int t, n;
    ll a;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        vec_i.clear();
        vec_a.clear();
        for (ll i = 1; i <= n; i++) {
            std::cin >> a;
            if (a < i) {
                vec_a.push_back(std::make_pair(i, a));
            }
        }
        ll ans = 0;
        n = vec_a.size();
        for (int i = 0; i < n; i++) {
            int j = std::lower_bound(vec_i.begin(), vec_i.end(), vec_a[i].second) - vec_i.begin();
            // if (j != vec_i.size() && vec_a[i].second == vec_i[j]) {
            //     j--;
            // }
            ans += j;
            vec_i.push_back(vec_a[i].first);
        }
        std::cout << ans << '\n';
    }
    return 0;
}