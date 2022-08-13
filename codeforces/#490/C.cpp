#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> vec[26];
std::vector<int> ans;

int main() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;
    for (int i = 0; i < n; i++) {
        vec[s[i] - 'a'].push_back(i);
    }
    int i = 0;
    while (k > 0) {
        if (k > vec[i].size()) {
            k -= vec[i].size();
        } else if (k == vec[i].size()) {
            for (int j = i + 1; j < 26; j++) {
                for (int k = 0; k < vec[j].size(); k++) {
                    ans.push_back(vec[j][k]);
                }
            }
            k -= vec[i].size();
        } else {
            for (int j = k; j < vec[i].size(); j++) {
                ans.push_back(vec[i][j]);
            }
            for (int j = i + 1; j < 26; j++) {
                for (int k = 0; k < vec[j].size(); k++) {
                    ans.push_back(vec[j][k]);
                }
            }
            k = 0;
        }
        i++;
    }
    std::sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        std::cout << s[ans[i]];
    }
    std::cout << '\n';
    return 0;
}