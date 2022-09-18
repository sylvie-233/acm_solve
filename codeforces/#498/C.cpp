#include <iostream>
#include <algorithm>
#include <set>

#define N 200005

typedef long long ll;

std::multiset<ll> st;

int a[N];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    ll suf_sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        suf_sum += a[i];
        st.insert(suf_sum);
    }
    ll ans = 0, sum = 0;
    for (int i = 0; i < n - 1; i++) {
        sum += a[i];
        st.erase(suf_sum);
        suf_sum -= a[i];
        if (st.count(sum) != 0) {
            ans = sum;
        }
    }
    std::cout << ans << '\n';
    return 0;
}
