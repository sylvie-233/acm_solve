#include <iostream>
#include <vector>
#include <algorithm>

#define N 200005

struct node {
    int p, size;
    std::vector<int> vec;
} d[N];

std::vector<int> vec_seq;

void dfs(int rt) {
    vec_seq.push_back(rt);
    d[rt].p = vec_seq.size() - 1;
    d[rt].size = 1;
    for (int i = 0; i < d[rt].vec.size(); i++) {
        dfs(d[rt].vec[i]);
        d[rt].size += d[d[rt].vec[i]].size;
    }
}

int main() {
    int n, q, p;
    std::cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        std::cin >> p;
        d[p].vec.push_back(i);
    }
    dfs(1);
    int u, k;
    while (q--) {
        std::cin >> u >> k;
        if (d[u].size < k) {
            std::cout << -1 << '\n';
        } else {
            std::cout << vec_seq[d[u].p + k - 1] << '\n';
        }
    }
    return 0;
}