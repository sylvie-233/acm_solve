#include <iostream>
#include <algorithm>
#include <queue>

const int N = 1005;

int n, m;
int arr[N][N];
bool vis[N][N];

int bfs(int x, int y) {
    int res = 0;
    std::queue<std::pair<int, int>> que;
    que.push({x, y});
    while (!que.empty()) {
        std::pair<int, int> p = que.front();
        que.pop();
        if (vis[p.first][p.second]) continue;
        res += arr[p.first][p.second];
        vis[p.first][p.second] = true;
        if (p.first > 1 && arr[p.first -1][p.second]) {
            que.push({p.first - 1, p.second});
        }
        if (p.first < n && arr[p.first + 1][p.second]) {
            que.push({p.first + 1, p.second});
        }
        if (p.second > 1 && arr[p.first][p.second - 1]) {
            que.push({p.first, p.second - 1});
        }
        if (p.second < m && arr[p.first][p.second + 1]) {
            que.push({p.first, p.second + 1});
        }
    }
    return res;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                vis[i][j] = false;
                std::cin >> arr[i][j];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (arr[i][j] && !vis[i][j]) {
                    ans = std::max(ans, bfs(i, j));
                }
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}