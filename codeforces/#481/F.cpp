#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#define N 200005

typedef std::pair<int, int> P;

bool used[N];
std::vector<int> G[N];
P d[N];
int s[N], data[N], res[N];

int main() {
    int n, k, a, b;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> data[i];
        s[i] = data[i];
        d[i].first = data[i];
        d[i].second = i;
    }
    while (k--) {
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    std::sort(d + 1, d + n + 1);
    std::sort(data + 1, data + n + 1);
    for (int i = 1; i <= n; i++) {
        int u = d[i].second, w = d[i].first;
        int cnt = 0;
        for (int j = 0; j < G[u].size(); j++) {
            if (used[G[u][j]] && w != s[G[u][j]]) {
                cnt++;
            }
        }
        used[u] = true;
        int p = std::lower_bound(data + 1, data + n + 1, w) - (data + 1);
        // std::cout << p << ' ' << cnt << '\n';
        // std::cout << p - cnt << ' ';
        res[u] = p - cnt;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}