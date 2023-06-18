using ll = long long;
int arr[20], len;
ll dp[50000][20];
const ll mod = 1e9 + 7;

int dfs(int cur, int cnt, int end_pos) {
    if (cnt == len) return 1;
    if (dp[cur][end_pos] != -1) return dp[cur][end_pos];
    int res = 0;
    for (int i = 0; i < len; i++) {
        if (!(cur & (1 << i))) {
            if (arr[i] % arr[end_pos] == 0 || arr[end_pos] % arr[i] == 0) {
                res = (res + dfs(cur | (1 << i), cnt + 1, i)) % mod;
            }
        }
    }
    return dp[cur][end_pos] = res;
}


class Solution {
public:
    int specialPerm(vector<int>& nums) {
        len = nums.size();
        
        for (int i = 0; i < (1 << len); i++) {
            for (int j = 0; j < len; j++) dp[i][j] = -1;
        }
        
        for (int i = 0; i < len; i++) arr[i] = nums[i];
        int res = 0;
        for (int i = 0; i < len; i++) {
            res = (res + dfs(1 << i, 1, i)) % mod;
        }
        return res;
    }
};