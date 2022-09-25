#include <iostream>
#include <algorithm>
#include <vector>

#define N 1005

struct node {
    int r, c, s;
};

std::vector<node> ans;

char ch[N][N];
bool acc[N][N];

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> ch[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ch[i][j] == '*') {
                int size = 1;
                while (ch[i + size][j] == '*'
                    && ch[i - size][j] == '*'
                    && ch[i][j + size] == '*'
                    && ch[i][j - size] == '*'
                    && i + size <= n
                    && i - size >= 1
                    && j + size <= m
                    && j - size >= 1) {
                        acc[i + size][j] = true;
                        acc[i - size][j] = true;
                        acc[i][j + size] = true;
                        acc[i][j - size] = true;   
                        size++;
                }
                if (size > 1) {
                    acc[i][j] = true;
                    ans.push_back({i, j, size - 1});
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ch[i][j] == '*' && !acc[i][j]) {
                std::cout << -1 << '\n';
                return 0;
            }
        }
    }
    std::cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i].r << ' ' << ans[i].c << ' ' << ans[i].s << '\n';
    }
    return 0;
}