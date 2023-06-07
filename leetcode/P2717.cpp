class Solution {
public:
    int semiOrderedPermutation(vector<int>& nums) {
        int start_p, end_p;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                start_p = i;
            } else if (nums[i] == nums.size()) {
                end_p = i;
            }
        }
        if (start_p < end_p) {
            return start_p - 1 + nums.size() - end_p;
        } else {
            return start_p - 1 + nums.size() - end_p - 1;
        }
    }
};