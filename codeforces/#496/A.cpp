#include <iostream>
#include <vector>

int a[1005];
std::vector<int> vec;

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int t;
        std::cin >> t;
        a[i] = t;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if ((a[i] + 1) != a[i + 1]) {
            ans++;
            vec.push_back(a[i]);
        }
    }
    std::cout << ans << '\n';
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}