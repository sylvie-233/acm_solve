#include <iostream>
#include <algorithm>

#define INF 0x3f3f3f3f

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        int a = 0, sum = 0, mn = INF;
        for (int i = 0; i < n; i++) {
            std::cin >> a;
            mn = std::min(mn, a);
            sum += a;
        }
        std::cout << sum - n * mn << '\n';
    }
    return 0;
}