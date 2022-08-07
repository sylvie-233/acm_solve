#include <iostream>

int a[55];

int main() {
    int t, n;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }
        bool f = true;
        for (int i = 3; i <= n; i += 2) {
            if ((a[i] % 2) != (a[i - 2] % 2)) {
                f = false;
                break;
            }
        }
        for (int i = 4; i <= n; i += 2) {
            if ((a[i] % 2) != (a[i - 2] % 2)) {
                f = false;
                break;
            }
        }
        std::cout << (f ? "YES" : "NO") << '\n';
    }
    return 0;
}