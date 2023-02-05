#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long ll;

int main() {
    int t, n;
    std::string s;
    std::cin >> t;
    std::vector<int> tmp;
    while (t--) {
        tmp.clear();
        std::cin >> n >> s;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'L') {
                sum += i;
            } else {
                sum += n - 1 - i;
            }
            if ((i == n / 2) && (n & 1)) {
                continue;
            }
            if (i < n / 2) {
                if (s[i] == 'L') {
                    tmp.push_back(n - 1 - i - i);
                }
            } else if (i >= n / 2) {
                if (s[i] == 'R') {
                    tmp.push_back(i - (n - 1 - i));
                }
            }
        }
        std::sort(tmp.rbegin(), tmp.rend());
        int len = tmp.size();
        int pos = 0;
        for (int i = 0; i < n; i++) {
            if (pos < len) {
                sum += tmp[pos];
                pos++;
            }
            std::cout << sum << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}