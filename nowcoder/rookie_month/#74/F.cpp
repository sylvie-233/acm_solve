#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

const int N = 2e5 + 5;

struct edge {
    int u, v, w;
} es[N];

std::vector<int> ks[N], vs[N]; 

int n, m, k;
int vis[N];

void dfs(int u, int color) {
    vis[u] = color;
    for (int v : vs[u]) {
        if (!vis[v]) dfs(v, color);
    }
}

bool check(int val) {
    std::memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) vs[i].clear();

    for (int i = 0; i < m; i++) 
        if (es[i].w <= val) {
            vs[es[i].u].push_back(es[i].v);
            vs[es[i].v].push_back(es[i].u);
        }

    int color = 1;
    for (int i = 1; i <= n; i++) 
        if (!vis[i]) dfs(i, color++);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < ks[i].size() - 1; j++)
            if (vis[ks[i][j]] != vis[ks[i][j + 1]])
                return false;
    return true;
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < m; i++)
        std::cin >> es[i].u >> es[i].v >> es[i].w;
    std::cin >> k;
    int s_i, q_i;
    for (int i = 0; i < k; i++) {
        std::cin >> s_i;
        for (int j = 0; j < s_i; j++) {
            std::cin >> q_i;
            ks[i].push_back(q_i);
        }
    }

    int l = 0, r = 1e9 + 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    }

    std::cout << r << '\n';
    
    return 0;
}