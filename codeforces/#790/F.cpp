#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

typedef std::pair<int, int> P;
std::map<int, int> mp;
std::vector<int> vec;

int main() {
    int t, n, k;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        mp.clear();
        vec.clear();
        int a;
        for (int i = 1; i <= n; i++) {
            std::cin >> a;
            mp[a]++;
        }
        for (auto x : mp) {
            if (x.second >= k) {
                vec.push_back(x.first);
            }
        }
        if (vec.size() == 0) {
            std::cout << "-1\n";
        } else {
            int ansl, ansr;
            int l = 1, r = 1, cnt = 0, ans = 0;
            // for (auto x : vec) {
            //     std::cout << x << " ";
            // }
            // std::cout << '\n';
            for (int i = 0; i < vec.size(); i++) {
                if (i == 0) {
                    l = vec[i];
                    r = vec[i];
                    cnt = 1;
                } else {
                    if (vec[i] != vec[i - 1] + 1) {
                        l = vec[i];
                        cnt = 1;
                    } else {
                        r = vec[i];
                        cnt++;
                    }
                }

                if (cnt > ans) {
                    ans = cnt;
                    ansl = l;
                    ansr = r;
                }
            }
            std::cout << ansl << ' ' << ansr << '\n';
        }
    }
    return 0;
}