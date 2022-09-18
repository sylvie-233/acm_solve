#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef std::pair<int, int> P;

int main() {
    int n, k, t;
    std::vector<P> v;
    std::vector<int> v_pos;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> t;
        v.push_back(P(t, i));
    }
    std::sort(v.begin(), v.end());
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += v[v.size() - 1 - i].first;
        v_pos.push_back(v[v.size() - 1 - i].second);
    }
    std::sort(v_pos.begin(), v_pos.end());
    // for (int i = 0; i < k; i++) {
    //     std::cout << v_pos[i] << ' ';
    // }
    // std::cout << '\n';
    std::cout << sum << '\n';
    int p = -1;
    for (int i = 0; i < k; i++) {
        if (i == k - 1) {
            std::cout << n - 1 - p;
        } else {
            std::cout << v_pos[i] - p << ' ';
            p = v_pos[i];
        }
    }
    std::cout << '\n';
    return 0;
}