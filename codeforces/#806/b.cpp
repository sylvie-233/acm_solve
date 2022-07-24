#include <iostream>
#include <cstring>

int arr[26];

int main() {
    int t, n, ans;
    char c;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        ans = 0;
        std::memset(arr, 0, sizeof(arr));
        for (int i = 0; i < n; i++) {
            std::cin >> c;
            if (arr[c - 'A']) {
                ans += 1;
            } else {
                ans += 2;
            }
            arr[c - 'A']++;
        }
        std::cout << ans << "\n";
    }
    return 0;
}