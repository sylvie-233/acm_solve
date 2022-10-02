#include <iostream>
#include <algorithm>

#define N 200005

int a[N];

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    bool flag = false;
    int ans = 1, t = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i - 1] * 2) {
            if (!flag) {
                flag = true;
                t = 2;
            } else {
                t++;
            }
        } else {
            flag = false;
            ans = std::max(ans, t);
        }
    }
    ans = std::max(ans, t);
    std::cout << ans << '\n';
    return 0;
}