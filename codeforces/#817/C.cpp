#include <iostream>
#include <string>
#include <map>

int main() {
    int t, n;
    std::string s;
    std::map<std::string, int> mp;
    std::cin >> t;
    while (t--) {
        mp.clear();
        std::cin >> n;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> s;
                if (mp.count(s) != 0) {
                    mp[s] = mp[s] | (1 << i);
                } else {
                    mp[s] = (1 << i);
                }
            }
        }
        int sco_1 = 0, sco_2 = 0, sco_3 = 0;
        for (auto it : mp) {
            if (it.second != 7) {
                if (it.second == 1) {
                    sco_1 += 3;
                    continue;
                }
                if (it.second == 2) {
                    sco_2 += 3;
                    continue;
                }
                if (it.second == 4) {
                    sco_3 += 3;
                    continue;
                }
                if (it.second & 1) {
                    sco_1 += 1;
                }
                if (it.second & 2) {
                    sco_2 += 1;
                }
                if (it.second & 4) {
                    sco_3 += 1;
                }
            }
        }
        std::cout << sco_1 << ' ' << sco_2 << ' ' << sco_3 << '\n';
    }
    return 0;
}