#include <iostream>
#include <cstring>

int a[10];

int main() {
    std::string s;
    int t, n, tmp;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> tmp >> s;
            for (int j = tmp - 1; j >= 0; j--) {
                if (s[j] == 'U') {
                    a[i] = (a[i] - 1 + 10) % 10;
                } else {
                    a[i] = (a[i] + 1) % 10;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << '\n';
    }
    return 0;
}