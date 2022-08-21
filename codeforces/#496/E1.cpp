#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
 
typedef long long ll;
 
int l[200005], r[200005], d[200005];
std::vector<int> vec;
std::map<int, int> mp;
 
int main() {
    int n, m;
    int p = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i];
        if (d[i] == m) {
            p = i;
        }
    }
    l[p] = r[p] = 0;
    for (int i = p - 1; i >= 1; i--) {
        if (d[i] < m) {
            l[i] = l[i + 1] + 1;
            r[i] = r[i + 1];
        } else {
            l[i] = l[i + 1];
            r[i] = r[i + 1] + 1;
        }
        mp[l[i] - r[i]]++;
    }
    mp[0]++;
    int cnt_l = 0, cnt_r = 0;
    ll ans = 0;
    for (int i = p; i <= n; i++) {
        if (i != p) {
            if (d[i] < m) {
                cnt_l++;
            } else {
                cnt_r++;
            }
        }
        int t = cnt_l - cnt_r;
        if (mp.count(0 - t)) {
            ans += mp[0 - t];
        }
        if (mp.count(-1 - t)) {
            ans += mp[-1 - t];
        }
    }
    std::cout << ans << '\n';
    return 0;
}