#include <iostream>

int a[1005];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] % 2 == 0) {
            a[i] -= 1;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}