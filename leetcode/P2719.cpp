using ll = long long;
const ll mod = 1e9 + 7;
const int N = 405;
ll memo[25][N];

class Solution {
    ll solve(string str, int min_sum, int max_sum) {
        memset(memo, -1, sizeof(memo));
        function<ll(int, int, bool)> dfs = [&](int pos, int sum, bool is_limit) -> ll {
            ll res = 0;
            if (sum > max_sum) return 0;
            if (pos == str.length()) return sum >= min_sum;
            if (!is_limit && memo[pos][sum] != -1) return memo[pos][sum];
            int r = is_limit ? str[pos] - '0' : 9;
            for (int i = 0; i <= r; i++) {
                res = (res + dfs(pos + 1, sum + i, is_limit && i == r)) % mod;
            }
            if (!is_limit) memo[pos][sum] = res;
            return res;
        };
        return dfs(0, 0, true);
    }
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        ll ans = (solve(num2, min_sum, max_sum) - solve(num1, min_sum, max_sum) + mod) % mod;
        int sum = 0;
        for (auto c : num1) {
            sum += c - '0';
        }
        return (ans + (min_sum <= sum && sum <= max_sum)) % mod;
    }
};