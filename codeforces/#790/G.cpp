#include <iostream>
#include <cstring>
#include <string>

#define N 5005

struct node {
    int to, next;
} es[N];

std::string s;
int cnt, head[N];
int W[N], B[N];

void add_edge(int u, int v) {
    es[cnt].to = v;
    es[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int rt) {
    if (s[rt - 1] == 'W') {
        W[rt]++;
    } else {
        B[rt]++;
    }
    // std::cout << rt << "-----\n";
    for (int i = head[rt]; ~i; i = es[i].next) {
        int v = es[i].to;
        dfs(v);
        W[rt] += W[v];
        B[rt] += B[v];
    }
}

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        cnt = 0;
        std::memset(head, -1, sizeof(head));
        std::memset(W, 0, sizeof(W));
        std::memset(B, 0, sizeof(B));
        int x;
        for (int i = 2; i <= n; i++) {
            std::cin >> x;
            add_edge(x, i);
        }
        std::cin >> s;
        // std::cout << "-------";
        dfs(1);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (W[i] == B[i]) {
                ans++;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}