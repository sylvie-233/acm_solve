#include <iostream>
#include <string>
#include <unordered_map>

typedef long long ll;

std::unordered_map<ll, int> mp;
std::string s[100005];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        mp.clear();
        for (int i = 0; i < n; i++) {
            std::cin >> s[i];
            ll t = 0;
            for (int j = 0; j < s[i].size(); j++) {
                t = t * 27 + s[i][j];
            }
            mp[t]++;
        }
        for (int i = 0; i < n; i++) {
            bool flag = false;
            ll t = 0;
            for (int j = 0; j < s[i].size(); j++) {
                t = t * 27 + s[i][j];
                if (mp[t]) {
                    ll tt = 0;
                    for (int k = j + 1; k < s[i].size(); k++) {
                        tt = tt * 27 + s[i][k];
                    }
                    if (mp[tt]) {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
        }
        std::cout << '\n';
    }
    return 0;
}