#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

typedef unsigned long long ull;
typedef std::pair<ull, int> P;

const ull b = 131, x = 173, mod = 17111354211743357;
std::string s[305];
int sum_len_s[305];
ull d_hash[305];
ull d_hash2[305];
std::vector<P> vec;

ull hashs(std::string s) {
    ull res = 0;
    for (int i = 0; i < s.length(); i++) {
        res = (res * b % mod + (s[i] - 'a' + 1)) % mod;
    }
    return res;
}

ull hashs2(std::string s) {
    ull res = 131;
    for (int i = 0; i < s.length(); i++) {
        res = ((res * x % mod)+ (s[i] - 'a' + 1)) % mod;
    }
    return res;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        sum_len_s[i] = sum_len_s[i - 1] + s[i].size();
        d_hash[i] = hashs(s[i]);
        d_hash2[i] = hashs2(s[i]);
    }
    int res = 0;
    for (int i = 1; i <= n / 2; i++) {
        vec.clear();
        for (int j = 1; j + i - 1 <= n; j++) {
            ull sum = 0;
            for (int k = j; k <= j + i - 1; k++) {
                sum = ((sum * x % mod )+ d_hash[k]) % mod;
            }
            ull sum2 = 0;
            for (int k = j; k <= j + i - 1; k++) {
                sum2 = ((sum2 * b) % mod + d_hash2[k]) % mod;
            }
            vec.push_back(P((sum + sum2) % mod, j));
        }
        std::sort(vec.begin(), vec.end());
        ull v = vec[0].first;
        int p = vec[0].second;
        int cnt = 1;
        int ans = 0;
        for (int j = 1; j < vec.size(); j++) {
            if (vec[j].first != vec[j - 1].first) {
                v = vec[j].first;
                p = vec[j].second;
                cnt = 1;
            } else {
                if (vec[j].second - p >= i) {
                    cnt++;
                    p = vec[j].second;
                    ans = std::max(ans, ((sum_len_s[p + i - 1] - sum_len_s[p - 1]) + (i - 1) - i) * cnt);
                }
            }
        }
        res = std::max(res, ans);
    }
    std::cout << sum_len_s[n] + n - 1 - res << '\n';
    return 0;
}