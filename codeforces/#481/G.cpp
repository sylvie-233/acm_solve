#include <iostream>
#include <algorithm>

struct node {
    int l, r, c, p;
} d[105];
int ans[105];

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> d[i].l >> d[i].r >> d[i].c;
        d[i].p = i;
    }
    // std::fill(ans + 1, ans + 1 + n, -1);
    std::sort(d + 1, d + 1 + m, [](node a, node b) {
        return a.r < b.r;
    });
    bool f = true;
    for (int i = 1; i <= m; i++) {
        int p = d[i].p, cnt = d[i].c;
        for (int j = d[i].l; j < d[i].r; j++) {
            if (!ans[j]) {
                ans[j] = p;
                cnt--;
            }
            if (cnt == 0) {
                break;
            }
        }
        if (cnt) {
            f = false;
            break;
        }
        if (!ans[d[i].r]) {
            ans[d[i].r] = m + 1;
        } else {
            f = false;
            break;
        }
    }
    if (!f) {
        std::cout << -1 << '\n';
    } else {
        for (int i = 1; i <= n; i++) {
            std::cout << ans[i] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}