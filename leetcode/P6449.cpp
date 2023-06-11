using ll = long long;

const int N = 2e3 +5;

int n, len, arr[N], mn[N][15];

int get_min(int l, int r) {
    int k = std::log2(r - l + 1);
    return std::min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

void init() {
    for (int i = 1; i <= n; i++) {
        mn[i][0] = arr[i]; 
    }
    // 长度递推
    for (int j = 1; j <= 14; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
}


class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        ll sum = 0;
        len = n = nums.size();
        for (int i = 1; i <= n; i++) {
            arr[i] = nums[i - 1];
            sum += arr[i];
        }
        for (int i = 1; i <= n; i++) {
            arr[i + n] = arr[i];
        }
        n *= 2;
        init();

        for (int i = 1; i < len; i++) {
            ll t_sum = 0;
            for (int j = 1; j <= len; j++) {
                t_sum += get_min(j, j + i);
            }
            sum = min(sum, t_sum + (ll)i * x);
        }

        return sum;
    }
};