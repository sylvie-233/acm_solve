#include <iostream>
#include <algorithm>
#include <string>

struct node {
    int p, cnt;
} d[105];

std::string s[105];
int n;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        d[i].p = i;
        d[i].cnt = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (s[i].find(s[j]) != std::string::npos) {
                d[j].cnt++;
            }
            if (s[j].find(s[i]) != std::string::npos) {
                d[i].cnt++;
            }
        }
    }
    
    std::sort(d + 1, d + 1 + n, [](node a, node b) {
        return a.cnt < b.cnt;
    });
    bool f = true;
    for (int i = 1; i <= n; i++) {
        if (!(d[i].cnt >= i)) {
            f = false;
            break;
        }
    }
    if (!f) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        for (int i = n; i >= 1; i--) {
            std::cout << s[d[i].p] << '\n'; 
        }
    }
    
    return 0;
}