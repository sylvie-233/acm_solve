#include <iostream>
#include <algorithm>
#include <vector>

#define N 300005
#define INF 1e9+5

struct node {
    int l, r, i;
} d[N];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> d[i].l >> d[i].r;
        d[i].i = i;
    }
    std::sort(d, d + n, [](node a, node b) {
        if (a.l != b.l) {
            return a.l < b.l;
        }
        return a.r > b.r;
    });
    int min_i = d[n - 1].i;

    std::sort(d, d + n, [](node a, node b) {
        if (a.r != b.r) {
            return a.r < b.r;
        }
        return a.l > b.l;
    });
    int max_i = d[0].i;
    // for (int i = 0; i < n; i++) {
    //     std::cout << d[i].l << '-' << d[i].r << '-' << d[i].i << '\n';
    // }

    // std::cout << min_i << '\n';
    // std::cout << max_i << '\n';
    int l = 0, r = INF, ans = 0;
    for (int i = 0; i < n; i++) {
        if (d[i].i != min_i) {
            l = std::max(l, d[i].l);
            r = std::min(r, d[i].r);
        }
    }
    ans = std::max(ans, r - l);

    l = 0, r = INF;
    for (int i = 0; i < n; i++) {
        if (d[i].i != max_i) {
            l = std::max(l, d[i].l);
            r = std::min(r, d[i].r);
        }
    }
    ans = std::max(ans, r - l);
    std::cout << ans << '\n';
    return 0;
}