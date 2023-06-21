#include <iostream>
#include <algorithm>

const int N = 2e5 + 5, T = 20;

struct node {
    int sum, min, max, l_min, l_max, r_min, r_max;
    
    node(int sum, int min, int max,int l_min, int l_max, int r_min, int r_max): sum(sum), min(min), max(max), l_min(l_min), l_max(l_max), r_min(r_min), r_max(r_max) {}
    node() : node(0, 0, 0, 0, 0, 0, 0) {}
    node(int x): sum(x) {
        min = l_min = r_min = std::min(0, x);
        max = l_max = r_max = std::max(0, x);
    }
    node rev() const {
        return node{sum, min, max, r_min, r_max, l_min, l_max};
    }
    friend node operator +(const node& L, const node& R) {
        node res;
        res.sum = L.sum + R.sum;
        res.l_min = std::min(L.l_min, L.sum + R.l_min);
        res.l_max = std::max(L.l_max, L.sum + R.l_max);
        res.r_min = std::min(R.r_min, R.sum + L.r_min);
        res.r_max = std::max(R.r_max, R.sum + L.r_max);
        res.min = std::min({L.min, R.min, L.r_min + R.l_min});
        res.max = std::max({L.max, R.max, L.r_max + R.l_max});
        return res;
    }
} ns[N][T];

int p[N][T], dep[N];

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        std::swap(u, v);
    }
    int d = dep[u] - dep[v];
    for (int i = 0; i < T; i++) {
        if ((d >> i) & 1) u = p[u][i];
    }
    if (u == v) return u;
    for (int i = T - 1; i >= 0; i--) {
        if (p[u][i] != p[v][i]) {
            u = p[u][i];
            v = p[v][i];
        }
    }
    return p[u][0];
}

node get_node(int u, int v) {
    int d = dep[u] - dep[v];
    node res;
    for (int i = 0; i < T; i++) {
        if ((d >> i) & 1) {
            res = res + ns[u][i];
            u = p[u][i];
        }
    }
    return res;
}


int main() {
    int t, n;
    dep[1] = 1;
    p[1][0] = 0;
    ns[1][0] = node(1);
    for (int i = 0; i + 1 < T; i++) {
        p[1][i + 1] = 0;
        ns[1][i + 1] = ns[1][i] + ns[0][i];
    }
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int pos = 2;
        std::string str;
        for (int i = 1; i <= n; i++) {
            std::cin >> str;
            if (str[0] == '+') {
                int v, x;
                std::cin >> v >> x;
                int u = pos++;
                dep[u] = dep[v] + 1;
                p[u][0] = v;
                ns[u][0] = node(x);
                for (int j = 0; j + 1 < T; j++) {
                    p[u][j + 1] = p[p[u][j]][j];
                    ns[u][j + 1] = ns[u][j] + ns[p[u][j]][j];
                }
            } else {
                int u, v, k;
                std::cin >> u >> v >> k;
                int lca_node = lca(u, v);
                node res = get_node(u, lca_node) + ns[lca_node][0] + get_node(v, lca_node).rev();
                if (res.min <= k && k <= res.max) {
                    std::cout << "YES\n";
                } else {
                    std::cout << "NO\n";
                }
            }
        }
    }
    return 0;
}