#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

#define N 200005

std::map<int, int> mp;

struct {
    int v, next;
} es[N << 1];
int n, m;
int cnt, head[N], deg[N];
bool used[N], able[N];

void add_edge(int u, int v) {
    es[cnt].v = v;
    es[cnt].next = head[u];
    head[u] = cnt++;
}

bool dfs(int u, int par) {
    used[u] = true;
    for (int i = head[u]; ~i; i= es[i].next) {
        int v = es[i].v;
        if (able[v] && v != par) {
            if (mp[v]) {
                return true;
            }
            mp[v]++;
            return dfs(v, u);
        }
    }
    return false;
}

int main() {
    cnt = 0;
    std::memset(head, -1, sizeof(head));
    std::cin >> n >> m;
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
        deg[u]++;
        deg[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 2) {
            able[i] = true;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (able[i] && !used[i]) {
            mp.clear();
            mp[i]++;
            if (dfs(i, 0)) {
                ans++;
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}