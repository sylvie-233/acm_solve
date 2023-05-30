#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> vec_01, vec_10, vec_11;

int main() {
    int t, n, m;
    std::string str;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        vec_01.clear();
        vec_10.clear();
        vec_11.clear();
        while (n--) {
            std::cin >> m >> str;
            if (str == "01") {
                vec_01.push_back(m);
            } else if (str == "10") {
                vec_10.push_back(m);
            } else if (str == "11") {
                vec_11.push_back(m);
            }
        }
        int ans = 1e6;
        std::sort(vec_01.begin(), vec_01.end());
        std::sort(vec_10.begin(), vec_10.end());
        std::sort(vec_11.begin(), vec_11.end());
        if (vec_11.size() != 0) {
            ans = std::min(ans, vec_11[0]);
        }
        if (vec_01.size() != 0 && vec_10.size() != 0) {
            ans = std::min(ans, vec_01[0] + vec_10[0]);
        }
        std::cout << (ans == 1e6 ? -1 : ans) << '\n';
    }
    return 0;
}