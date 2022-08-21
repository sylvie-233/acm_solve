#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::vector<int> vec;
    std::cin >> s;
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        int t = s[i] - '0';
        if (t % 3 == 0) {
            ans++;
            vec.clear();
        } else {
            bool f = false;
            for (int j = vec.size() - 1; j >= 0; j--) {
                if ((vec[j] + t) % 3 == 0) {
                    f = true;
                    break;
                }
                vec[j] += t;
            }
            if (f) {
                ans++;
                vec.clear();
            } else {
                vec.push_back(t);
            }   
        }
    }
    std::cout << ans << '\n';
    return 0;
}