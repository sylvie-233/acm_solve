#include <iostream>
#include <algorithm>
#include <vector>

#define INF 0x3f3f3f3f

typedef long long ll;

bool used[20];
int d[20];

std::vector<int> vec[10];

int main() {
    ll n;
    std::cin >> n;
    if (n % 25 == 0) {
        std::cout << "0\n";
        return 0;
    }
    int i = 1, len = 0;
    while (n) {
        int v = n % 10;
        d[i] = v;
        vec[v].push_back(i);
        n /= 10;
        i++;
        len++;
    }
    int ans = INF;
    if (vec[0].size() >= 2) {
        ans = std::min(ans, vec[0][0] - 1 + vec[0][1] - 2);  
    }
    if (vec[2].size() >= 1 && vec[5].size() >= 1) {
        std::fill(used, used + 20, false);
        used[vec[2][0]] = true;
        used[vec[5][0]] = true;
        if (used[len] && d[len - 1] == 0) {
            int p = 0;
            for (int i = len - 2; i >= 1; i--) {
                if (d[i] != 0 && !used[i]) {
                    p = i;
                    break;
                }
            }
            if (p != 0) {
                int mn = std::min(vec[2][0], vec[5][0]);
                int t = 0;
                if (p < mn) {
                    t = -1;
                }
                int t2 = 0;
                if (vec[2][0] < vec[5][0]) {
                    t2 = 1;
                }
                ans = std::min(ans, vec[5][0] + vec[2][0] - 3 + t + len - 1 - p + t2);
            }
        } else {
            int t2 = 0;
            if (vec[2][0] < vec[5][0]) {
                t2 = 1;
            }
            ans = std::min(ans, vec[5][0] + vec[2][0] - 3 + t2);
        }
    }
    if (vec[5].size() >= 1 && vec[0].size() >= 1) {
        std::fill(used, used + 20, false);
        used[vec[5][0]] = true;
        used[vec[0][0]] = true;
        if (used[len] && d[len - 1] == 0) {
            if (vec[0][0] == len - 1) {
                ans = std::min(ans, vec[5][0] + vec[0][0] - 3);
            } else {
                int p = 0;
                for (int i = len - 2; i >= 1; i--) {
                    if (d[i] != 0 && !used[i]) {
                        p = i;
                        break;
                    }
                }
                if (p != 0) {
                    int mn = std::min(vec[5][0], vec[0][0]);
                    int t = 0;
                    if (p < mn) {
                        t = -1;
                    }
                    int t2 = 0;
                    if (vec[5][0] < vec[0][0]) {
                        t2 = 1;
                    }
                    ans = std::min(ans, vec[5][0] + vec[0][0] - 3 + t + len - 1 - p + t2);
                }
            }
            
        } else {
            int t2 = 0;
            if (vec[5][0] < vec[0][0]) {
                t2 = 1;
            }
            ans = std::min(ans, vec[5][0] + vec[0][0] - 3 + t2);
        }
    }
    if (vec[7].size() >= 1 && vec[5].size() >= 1) {
        std::fill(used, used + 20, false);
        used[vec[7][0]] = true;
        used[vec[5][0]] = true;
        if (used[len] && d[len - 1] == 0) {
            int p = 0;
            for (int i = len - 2; i >= 1; i--) {
                if (d[i] != 0 && !used[i]) {
                    p = i;
                    break;
                }
            }
            if (p != 0) {
                int mn = std::min(vec[7][0], vec[5][0]);
                int t = 0;
                if (p < mn) {
                    t = -1;
                }
                int t2 = 0;
                if (vec[7][0] < vec[5][0]) {
                    t2 = 1;
                }
                ans = std::min(ans, vec[7][0] + vec[5][0] - 3 + t + len - 1 - p + t2);
            }
        } else {
            int t2 = 0;
            if (vec[7][0] < vec[5][0]) {
                t2 = 1;
            }
            ans = std::min(ans, vec[7][0] + vec[5][0] - 3 + t2);
        }
    }
    
    
    if (ans == INF) {
        ans = -1;
    }
    std::cout << ans << '\n';
    return 0;
}