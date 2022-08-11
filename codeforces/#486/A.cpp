#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

typedef std::pair<int, int> P;

P a[105];

int main() {
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].first;
        a[i].second = i;
    }
    std::sort(a + 1, a + 1 + n);
    int cnt = 0;
    std::vector<int> vec;
    for (int i = 1; i <= n; i++) {
        if (a[i].first != a[i - 1].first) {
            cnt++;
            vec.push_back(a[i].second);
        }
    }
    if (cnt < k) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        for (int i = 0; i < k; i++) {
            std::cout << vec[i] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}