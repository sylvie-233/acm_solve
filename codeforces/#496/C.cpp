#include <iostream>
#include <algorithm>
#include <map>

std::map<int, int> mp, cnt;
int d[120005];

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i];
        for (int j = 1; j <= 30; j++) {
            int t = 1 << j;
            if (t > d[i]) {
                if (t == 2 * d[i]) {
                    if (cnt[d[i]]) {
                        mp[t - d[i]]++;
                    }
                    cnt[d[i]]++;
                } else {
                    mp[t - d[i]]++;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!mp[d[i]]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    return 0;
}