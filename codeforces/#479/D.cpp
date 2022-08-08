#include <iostream>
#include <algorithm>

typedef long long ll;

struct node {
    ll v;
    int cnt_3, cnt_2;
} d[105];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> d[i].v;
        ll t = d[i].v;
        while (t && t % 3 == 0) {
            t /= 3;
            d[i].cnt_3++;
        }
        while (t && t % 2 == 0) {
            t /= 2;
            d[i].cnt_2++;
        }
    }
    std::sort(d, d + n, [](node a, node b) {
        if (a.cnt_3 != b.cnt_3) {
            return a.cnt_3 > b.cnt_3;
        }
        return a.cnt_2 < b.cnt_2;
    });
    for (int i = 0; i < n; i++) {
        std::cout << d[i].v << ' ';
    }
    std::cout << '\n';
    // for (int i = 0; i < n; i++) {
    //     std::cout << d[i].v << ' ' << d[i].cnt_3 << ' ' << d[i].cnt_2 << '\n';
    // }
    return 0;
}