#include <iostream>
#include <map>
 
#define N 1005
 
std::map<int, int> mp;
int d[N];
 
int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        mp.clear();
        int a;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            std::cin >> a;
            for (auto p = mp.lower_bound(a); p != mp.end(); p++) {
                ans += p->second;
            }
            mp[a]++;
        }
        std::cout << ans << '\n';
    }
    return 0;
}