#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string s, t;
    std::cin >> s >> t;
    int len = std::min(s.length(), t.length());
    int cnt = 0;
    while (s[s.length() - 1 - cnt] == t[t.length() - 1 - cnt] && cnt < len) {
        cnt++;
    }
    std::cout << s.length() + t.length() - 2 * cnt << '\n';
    return 0;
}