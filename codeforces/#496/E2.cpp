#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long ll;

int l[200005], r[200005], d[200005];
int p[200005];
std::vector<int> vec;
std::map<int, int> mp;


// TODO 超时代码：暴力算法
int main() {
    int n, m;
    int p = 0;
    std::cin >> n >> m;
    vec.push_back(0);
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i];
        if (d[i] == m) {
            vec.push_back(i);
        }
    }

    // bool f = true;
    // for (int i = 1; i <= n; i++) {
    //     if (d[i] != m ) {
    //         f = false;
    //         break;
    //     }
    // }

    // if (f) {
    //     std::cout << ((ll)1) * n * (n + 1) / 2 << std::endl;
    //     return 0;
    // }

    ll ans = 0;
    for (int i = 1; i < vec.size(); i++) {
        int cnt_l = 0, cnt_r = 0;
        mp.clear();
        for (int j = vec[i]; j > vec[i - 1]; j--) {
            if (j != vec[i]) {
                if (d[j] > m) {
                    l[j] = l[j + 1];
                    r[j] = r[j + 1] + 1;
                } else if (d[j] < m) {
                    l[j] = l[j + 1] + 1;
                    r[j] = r[j + 1];
                }
            } else {
                l[j] = r[j] = 0;
            }
            mp[l[j] - r[j]]++;
        }
        int cnt_m = 0;

        for (int j = vec[i]; j <= n; j++) {
            if (j != vec[i]) {
                if (d[j] > m) {
                    cnt_r++;
                } else if (d[j] < m) {
                    cnt_l++;
                }
            } else {
                cnt_l = cnt_r = 0;
            }
            if (d[j] == m) {
                cnt_m++;
            }

            for (int k = -cnt_m; k <= cnt_m - 1; k++) {
                if (mp.count(k - (cnt_l - cnt_r))) {
                    ans += mp[k - (cnt_l - cnt_r)];
                }
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}