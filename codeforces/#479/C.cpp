#include <iostream>
#include <algorithm>

int d[200005];

int main() {
    int n, k;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    std::sort(d, d + n);
    int ans = -1;
    if (k == 0) {
        if (d[0] == 1) {
           ans = -1; 
        } else {
            ans = d[0] - 1;
        }
    } else {
        ans = d[k - 1];
        if (k < n) {
            if (d[k] == d[k - 1]) {
                ans = -1;
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}