#include <iostream>
#include <algorithm>
#include <vector>

struct node {
    int v, i, p;
} d[200005];
int data[200005];
int cnt;

int main() {
    int k, n, a;
    std::cin >> k;
    for (int i = 1; i <= k; i++) {
        std::cin >> n;
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            std::cin >> data[j];
            sum += data[j];
        }        
        for (int j = 1; j <= n; j++) {
            d[cnt].v = sum - data[j];
            d[cnt].i = i;
            d[cnt++].p = j;
        }
    }
    std::sort(d, d + cnt, [](node a, node b) {
        if (a.v != b.v) {
            return a.v < b.v;
        }
        return a.i < b.i;
    });
    bool f = false;
    for (int i = 0; i < cnt - 1; i++) {
        if (d[i].v == d[i + 1].v && d[i].i != d[i + 1].i) {
            std::cout << "YES\n";
            std::cout << d[i].i << ' ' << d[i].p << '\n';
            std::cout << d[i + 1].i << ' ' << d[i + 1].p << '\n';
            f = true;
            break;
        }
    }
    if (!f) {
        std::cout << "NO\n";
    }
    return 0;
}