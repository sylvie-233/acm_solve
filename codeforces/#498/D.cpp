#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define N 100005

char a[N], b[N];
int ch[26];
std::vector<int> vec;

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
    }
    int m = (n % 2) ? n / 2 + 1 : n / 2;
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (n % 2 && i == m) {
            if (!(a[i] == b[i])) {
                ans++;
            }
            continue;
        }
        if (b[i] == b[n - i + 1]) {
            if (!(a[i] == a[n - i + 1])) {
                ans += 1;
            }
        } else {
            if ((a[i] == b[i] && a[n - i + 1] == b[n - i + 1]) || (a[i] == b[n - i + 1] && a[n - i + 1] == b[i])) {
                continue;
            } else {
                if (a[i] == b[i] || a[n - i + 1] == b[i] || a[i] == b[n - i + 1] || a[n - i + 1] == b[n - i + 1]) {
                    ans += 1;
                } else {
                    ans += 2;
                }
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}