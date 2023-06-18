class Solution {
public:
    int findValueOfPartition(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 1e9 + 7;
        for (int i = 0; i < nums.size() - 1; i++) {
            res = min(res, nums[i + 1] - nums[i]);
        }
        return res;
    }
};