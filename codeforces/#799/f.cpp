#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

#define N 11

int cnt[N];

std::vector<std::vector<std::pair<int, int>>> vec;

void init() {
    std::unordered_map<int, int> mp;
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            for (int k = j; k < 10; k++) {
                if ((i + j + k) % 10 == 3) {
                    mp.clear();
                    // std::cout << std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(k) << std::endl;
                    mp[i]++;
                    mp[j]++;
                    mp[k]++;
                    std::vector<std::pair<int, int>> tmp;
                    for (auto x : mp) {
                        // std::cout << std::to_string(x.first) + " " + std::to_string(x.second) << std::endl;
                        tmp.push_back(std::make_pair(x.first, x.second));
                    }
                    vec.push_back(tmp);
                }
            }
        }
    }
}

int main() {
    init();
    
    int t, n, x;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        std::memset(cnt, 0, N * sizeof(int));
        while (n--) {
            std::cin >> x;
            cnt[x % 10]++;
        }
        bool flag = false;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].size() == 1) {
                if (cnt[vec[i][0].first] - vec[i][0].second >= 0) {
                    flag = true;
                    // std::cout << std::to_string(vec[i][0].first) << std::endl;
                    break;
                } 
            } else if (vec[i].size() == 2) {
                if ((cnt[vec[i][0].first] - vec[i][0].second >= 0)
                    && (cnt[vec[i][1].first] - vec[i][1].second >= 0)) {
                    flag = true;
                    // std::cout << std::to_string(vec[i][0].first) + " " + std::to_string(vec[i][1].first) << std::endl;
                    break;
                } 
            } else if (vec[i].size() == 3) {
                if ((cnt[vec[i][0].first] - vec[i][0].second >= 0)
                    && (cnt[vec[i][1].first] - vec[i][1].second >= 0)
                    && (cnt[vec[i][2].first] - vec[i][2].second >= 0)) {
                    flag = true;
                    // std::cout << std::to_string(vec[i][0].first) + " " + std::to_string(vec[i][1].first) + " " + std::to_string(vec[i][2].first) << std::endl;
                    break;
                } 
            }
        }
        std::cout << (flag ? "YES" : "NO") << std::endl;
    }

    return 0;
}