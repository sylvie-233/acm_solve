#include <iostream>
#include <algorithm>

const int N = 2e3 + 5;

int sum[N];

void init_sum() {
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i - 1] + i;
    }
}


int main() {
    init_sum();
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int pos = std::lower_bound(sum + 1, sum + N, n) - sum;
        // std::cout << pos << '\n';
        if (sum[pos] == n) {
            for (int i = 1; i <= pos; i++) {
                std::cout << i << ' ';
            }
        } else {
            for (int i = 1; i < pos; i++) {
                std::cout << (i == pos - 1 ? i + n - sum[i] : i) << ' ';
            }
        }
        std::cout << '\n';
    }
    return 0;
}