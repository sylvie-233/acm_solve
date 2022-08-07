#include <iostream>
#include <unordered_map>

std::unordered_map<int, int> mp;

int main() {
    int t, n, a;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int ans = -1;
        mp.clear();
        while (n--) {
            std::cin >> a;
            if (++mp[a] >= 3) {
                ans = a;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}