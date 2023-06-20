#include <iostream>
#include <string>
#include <algorithm>

const int N = 2e5 + 5;


int n, ns_cnt[N][2][2];

int main() {
    int t, v, x, u, k;
    std::string str;
    std::cin >> t;
    while (t--) {
        int pos = 2;
        std::cin >> n;
        for (int i = 0; i <= n; i++) ns_cnt[i][0][0] = ns_cnt[i][0][1] = ns_cnt[i][1][0] = ns_cnt[i][1][1] = 1;
        ns_cnt[1][0][0] = ns_cnt[1][0][1] = 0;
        ns_cnt[1][1][0] = ns_cnt[1][1][1] = 1;
        for (int i = 1; i <= n; i++) {
            std::cin >> str;
            if (str[0] == '+') {
                std::cin >> v >> x;
                ns_cnt[pos][0][0] = std::min(ns_cnt[v][0][0], ns_cnt[v][1][0]); 
                ns_cnt[pos][0][1] = std::max(ns_cnt[v][0][1], ns_cnt[v][1][1]); 
                ns_cnt[pos][1][0] = std::min(x, ns_cnt[v][1][0] + x);
                ns_cnt[pos][1][1] = std::max(x, ns_cnt[v][1][1] + x); 
                pos++;
            } else {
                std::cin >> u >> v >> k;
                if (k >= std::min(ns_cnt[v][0][0], ns_cnt[v][1][0]) &&
                    k <= std::max(ns_cnt[v][0][1], ns_cnt[v][1][1])) {
                        std::cout << "YES\n";
                } else {
                    std::cout << "NO\n";
                }
            }
        }

    }
    return 0;
}