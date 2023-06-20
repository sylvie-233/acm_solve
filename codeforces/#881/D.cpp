#include <iostream>
#include <vector>
#include <algorithm>

const int N = 2e5 + 5;

using ll = long long;

int node_cnt[N];
bool vis[N];

std::vector<int> ns[N];

int dfs(int u, int p) {
    vis[u] = true;
    if (ns[u].size() == 1 && ns[u][0] == p) return node_cnt[u] = 1;
    node_cnt[u] = 0;
    for (int i = 0; i < ns[u].size(); i++) {
        if (!vis[ns[u][i]])
            node_cnt[u] += dfs(ns[u][i], u);
    }
    return node_cnt[u];
}

int main() {
    int t, n, q, u, v, x, y;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            ns[i].clear();
            vis[i] = false;
        }
        for (int i = 1; i < n; i++) {
            std::cin >> u >> v;
            ns[v].push_back(u);
            ns[u].push_back(v);
        }
        dfs(1, 0);
        std::cin >> q;
        while (q--) {
            std::cin >> x >> y;
            std::cout << (ll)node_cnt[x] *  node_cnt[y] << '\n';
        }
    }
    return 0;
}