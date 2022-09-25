#include <iostream>
#include <algorithm>
#include <vector>

#define N 100005

typedef long long ll;


int n;
ll m, sum_b, sum_a;
std::vector<ll> sum_;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, b;
        std::cin >> a >> b;
        sum_a += a;
        sum_b += b;
        sum_.push_back(a - b);
    }
    if (sum_b > m) {
        std::cout << -1 << '\n';
    } else {
        if (sum_a <= m) {
            std::cout << 0 << '\n';
        } else {
            ll dis = sum_a - m;
            int cnt = 0;
            std::sort(sum_.begin(), sum_.end());
            for (int i = n -1; i >= 0; i--) {
                cnt++;
                dis -= sum_[i];
                if (dis <= 0) {
                    break;
                }
            }
            std::cout << cnt << '\n';
        }
    }
    return 0;
}