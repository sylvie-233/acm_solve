class Solution {
public:
    int minimizedStringLength(string s) {
        int ans = 1;
        sort(s.begin(), s.end());
        for (int i = 1; i < s.length(); i++) {
            if (s[i] != s[i - 1]) {
                ans++;
            }
        }
        return ans;
    }
};