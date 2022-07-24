#include <iostream>
#include <algorithm>
 
typedef long long ll;
 
int a[100005];
 
int main() {
    int t, n, k;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        ll sum = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            ll tmpSum = 0;
            unsigned long long tmp = 2;
            for (int j = i; j < std::min(n, i + 31); j++) {
                tmpSum += a[j] / tmp;
                tmp <<= 1;
            }
            ans = std::max(ans, sum + tmpSum);
            sum += a[i] - k;
        }
        ans = std::max(ans, sum);
        std::cout << ans << '\n';
    }
    return 0;
}