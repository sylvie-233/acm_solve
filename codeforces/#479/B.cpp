#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    int n;
    int cnt = 0;
    std::string s, ans;
    std::unordered_map<std::string, int> mp;
    std::cin >> n >> s;
    ans = s.substr(0, 2);
    for (int i = 0; i < s.length() -1; i++) {
        std::string t = s.substr(i, 2);
        if (++mp[t] > cnt) {
            ans = t;
            cnt = mp[t];
        }
    }
    std::cout << ans << '\n';
    return 0;
}