const int N = 1e4 + 5;


bool vis_r[N], vis_c[N];

class Solution {
public:
    long long matrixSumQueries(int n, vector<vector<int>>& queries) {
        fill(vis_r, vis_r + n, false);
        fill(vis_c, vis_c + n, false);
        int cnt_r = n, cnt_c = n;
        long long res = 0;
        for (int i = queries.size() - 1; i >= 0; i--) {
            if (queries[i][0] == 0) {
                if (!vis_r[queries[i][1]]) {
                    vis_r[queries[i][1]] = true;
                    cnt_c--;
                    res += (long long ) 1 * cnt_r * queries[i][2];
                }
            } else {
                if (!vis_c[queries[i][1]]) {
                    vis_c[queries[i][1]] = true;
                    cnt_r--;
                    res += (long long ) 1 * cnt_c * queries[i][2];
                }
            }
        }
        return res;
    }
};