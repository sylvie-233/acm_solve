#include <iostream>
#include <algorithm>

const int N = 55;

int arr[N];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            std::cin >> arr[i];
        }
        std::sort(arr + 1, arr + 1 + n);
        int res = 0;
        for (int i = 1; i <= n / 2; i++) {
            res += arr[n + 1 - i] - arr[i];
        }
        std::cout << res << '\n';
    }
    return 0;
}