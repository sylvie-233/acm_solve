#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    int n;
    std::string s;
    std::vector<int> vec;
    std::cin >> n >> s;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            vec.push_back(i);
            if (i != n / i) {
                vec.push_back(n / i);
            }
        }
    }
    vec.push_back(n);
    std::sort(vec.begin(), vec.end());
    // for (int i = 0; i < vec.size(); i++) {
    //     std::cout << vec[i] << ' ';
    // }
    // std::cout << '\n';
    for (int i = 0; i < vec.size(); i++) {
        std::string t = s.substr(0, vec[i]);
        std::string t2 = s.substr(vec[i]);
        std::string t3 = std::string(t.rbegin(), t.rend());
        s = t3 + t2;
        // std::cout << t3 << '-' << t2 << '-' << s << '\n';
    }
    std::cout << s << '\n';
    return 0;
}