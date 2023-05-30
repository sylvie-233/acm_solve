#include <iostream>
#include <algorithm>

const int N = 105;

int arr[N];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 0; i < n; i++) std::cin >> arr[i];
        int ans = 0, tmp = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                tmp++;
                ans = std::max(ans, tmp);
            } else {
                tmp = 0;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}