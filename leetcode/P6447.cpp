const int N = 505;

int dp[N];

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int len = cost.size();
        fill(dp, dp + N, 1e9 + 5);
        dp[0] = 0;
        for (int i = 0; i < len; i++) {
            for (int j = len; j >= 1; j--) {
                for (int k = time[i] + 1; k >= 1; k--) {
                    if (j < k) continue;
                    dp[j] = min(dp[j], dp[j - k] + cost[i]);
                }
            }
        }
        return dp[len];
    }
};