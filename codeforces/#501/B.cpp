#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    int n;
    std::string s, t;
    std::cin >> n >> s >> t;
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) {
            int p = -1;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == t[i]) {
                    p = j;
                    break;
                }
            }
            if (p == -1) {
                std::cout << -1 << '\n';
                return 0;
            } else {
                while (p != i) {
                    std::swap(s[p], s[p - 1]);
                    ans.push_back(p);
                    p--;
                }
            }
        }
    }
    std::cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}