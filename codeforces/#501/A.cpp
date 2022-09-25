#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef std::pair<int, int> P;
P d[105];

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> ans;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i].first >> d[i].second;
    }
    for (int i = 1; i <= m; i++) {
        bool f = false;
        for (int j = 1; j <= n; j++) {
            if (i <= d[j].second && i >= d[j].first) {
                f = true;
                break;
            }
        }
        if (!f) {
            ans.push_back(i);
        }
    }
    std::cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}