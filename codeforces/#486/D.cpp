#include <iostream>
#include <algorithm>
#include <set>
#include <map>

typedef long long ll;

std::map<int, int> mp;
std::set<int> st;

int main() {
    int n;
    ll a;
    std::cin >> n;
    mp.clear();
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        mp[a]++;
        st.insert(a);
    }
    int ans = 0, p = 0, op = 0;
    for (auto i = st.begin(); i != st.end(); i++) {
        int v = *i;
        int w = mp[v];
        for (int j = 0; j <= 33; j++) {
            ll v1 = (ll)v + (((ll)1) << j);
            if (v1 > 1e9) {
                continue;
            }
            int c1 = mp[v1];
            ll v2 = (ll)v + (((ll)1) << (j + 1));
            int c2 = 0;
            if (v2 <= 1e9) {
                c2 = mp[v2];
            }
            // int c1 = 0, c2 = 0;
            if ((w + c1 + c2) > ans) {
                ans = w + c1 + c2;
                p = v;
                op = j;
            }
        }
    }
    std::cout << ans << '\n';
    ll v = p;
    int cnt = mp[v];
    while (cnt--) {
        std::cout << v << ' ';
    }
    v = p + ((ll)1 << op);
    if (v <= 1e9) {
        cnt = mp[v];
        while (cnt--) {
            std::cout << v << ' ';
        }
    }
    v = p + ((ll)1 << (op + 1));
    if (v <= 1e9) {
        cnt = mp[v];
        while (cnt--) {
            std::cout << v << ' ';
        }
    }
    std::cout << '\n';
    return 0;
}