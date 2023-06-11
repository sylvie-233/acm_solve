class Solution {
public:
    string smallestString(string s) {
        int l = -1, r = -1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != 'a') {
                r = l = i;
                break;
            }
        }
        if (l != -1) {
            for(; r < s.length(); r++) {
                if (s[r] == 'a') break;
            }
            for (int i = l; i < r; i++) {
                s[i] = s[i] - 1;
            }
        } else {
            s[s.length() - 1] = 'z';
        }
        return s;
    }
};