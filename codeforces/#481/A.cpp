#include <iostream>
#include <vector>

int a[55];
bool used[1005];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> vec;
    for (int i = n - 1; i >= 0; i--) {
        if (!used[a[i]]) {
            used[a[i]] = true;
            vec.push_back(a[i]);
        }
    }
    std::cout << vec.size() << '\n';
    for (int i = vec.size() - 1; i >= 0; i--) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}