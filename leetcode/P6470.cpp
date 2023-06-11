class Solution {
public:
    int findNonMinOrMax(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums[0] == nums[nums.size() - 1]) {
            return -1;
        } else {
            int cnt_min = 0, cnt_max = 0;
            for (auto it : nums) {
                if (it == nums[0]) {
                    cnt_min++;
                } else if (it == nums[nums.size() - 1]) {
                    cnt_max++;
                }
            }
            if ((cnt_min + cnt_max) == nums.size()) {
                return -1;
            } else {
                return nums[cnt_min];
            }
        }
    }
};