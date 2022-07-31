#include <iostream>
#include <cstring>
#include <map>

typedef long long ll;

#define N 200005

std::map<int, int> mp;

int n;
ll bit[N];

ll sum(int i) {
    ll res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & -i;
    }
    return res;
}

void add(int i, int v) {
    while (i <= n) {
        bit[i] += v;
        i += i & -i;
    }
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        mp.clear();
        std::memset(bit, 0, (n + 1) * sizeof(ll));
        int a;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            std::cin >> a;
            auto p = mp.lower_bound(a);
            
            if (p != mp.end()) {
                // std::cout << i << "-----" << p->first << "\n";
                // std::cout << i << "-----sum:" << sum(n) << "\n";
                // std::cout << i << "-----sum:" << sum(n) - sum(p->first - 1) << "\n";
                ans += sum(n) - sum(p->first - 1);
            }
            mp[a]++;
            add(a, 1);
        }
        std::cout << ans << '\n';
    }
    return 0;
}