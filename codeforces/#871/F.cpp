#include <iostream>
#include <vector>

const int N = 205;
std::vector<int> edge[N];

int main() {
    int t, n, m, u, v;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        for (int i = 1; i <= n; i++) edge[i].clear();
        while (m--) {
            std::cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int start_p = 0;
        for (int i = 1; i <= n; i++) {
            if (edge[i].size() == 1) {
                start_p = i;
                break;
            }
        }
        int p_parent = edge[start_p][0];
        int center_p = 0;
        for (int i = 0; i <= edge[p_parent].size(); i++) {
            if (edge[edge[p_parent][i]].size() != 1) {
                center_p = edge[p_parent][i];
                break;
            }
        }
        std::cout << edge[center_p].size() << " " << edge[p_parent].size() - 1 << '\n';
    }
    return 0;
}