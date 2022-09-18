#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <map>

#define N 25

typedef long long ll;
typedef std::pair<int, ll> P;

struct node {
    int i, j;
    ll v;
};

std::map<P, ll> mp;
std::vector<P> vec;
ll g[N][N];

int main() {
    int n, m;
    ll k;
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> g[i][j];
        }
    }
    std::queue<node> que;
    int mid = (n + m + 2) / 2;
    que.push({1, 1, g[1][1]});
    while (!que.empty()) {
        node t = que.front();
        que.pop();
        if (t.i + t.j == mid) {
            mp[{t.i, t.v}] += 1;
            continue;
        }
        if (t.i < n) {
            que.push({t.i + 1, t.j, t.v ^ g[t.i + 1][t.j]});
        }
        if (t.j < m) {
            que.push({t.i, t.j + 1, t.v ^ g[t.i][t.j + 1]});
        }
    }

    que.push({n, m, g[n][m]});
    while (!que.empty()) {
        node t = que.front();
        que.pop();
        if (t.i + t.j == mid) {
            vec.push_back({t.i, t.v ^ g[t.i][t.j]});
            continue;
        }
        if (t.i > 1) {
            que.push({t.i - 1, t.j, t.v ^ g[t.i - 1][t.j]});
        }
        if (t.j > 1) {
            que.push({t.i, t.j - 1, t.v ^ g[t.i][t.j - 1]});
        }
    }

    ll ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        ans += mp[{vec[i].first, vec[i].second ^ k}];
    }
    std::cout << ans << '\n';
    return 0;
}