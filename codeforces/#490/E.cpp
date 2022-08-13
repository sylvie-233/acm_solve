#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>
#include <queue>

#define N 5005

struct {
    int v, next;
} edge[N];
int cnt, head[N];
int top, flag, tot, sta[N], dfn[N], low[N], id[N];
bool used[N];

bool mark[N];
int in[N];

void add_edge(int u, int v) {
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void init() {
    cnt = top = flag = tot = 0;
    std::memset(head, -1, sizeof(head));
    std::memset(dfn, 0, sizeof(dfn));
    std::memset(used, 0, sizeof(used));
}

void tarjin(int u) {
    dfn[u] = low[u] = ++flag;
    used[u] = true;
    sta[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (mark[v]) {
            continue;
        }
        if (!dfn[v]) {
            tarjin(v);
            low[u] = std::min(low[u], low[v]);
        } else if (used[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        tot++;
        int t;
        do {
            t = sta[--top];
            used[t] = false;
            id[t] = tot;
        } while(t != u);
    }
}

void bfs(int s) {
    std::queue<int> que;
    que.push(s);
    mark[s] = true;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].v;
            if (!mark[v]) {
                que.push(v);
                mark[v] = true;
            }
        }
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    init();
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        add_edge(u, v);
    }
    bfs(s);
    std::vector<int> vec;
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) {
            vec.push_back(i);
            if (!dfn[i]) {
                tarjin(i);
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        int u = vec[i];
        for (int j = head[u]; ~j; j = edge[j].next) {
            int v = edge[j].v;
            if (!mark[v] && (id[u] != id[v])) {
                in[id[v]]++;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= tot; i++) {
        if (!in[i]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    return 0;
}