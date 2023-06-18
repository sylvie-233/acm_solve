class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int cnt = 0, res = 0;
        int t = mainTank / 5;
        res = mainTank % 5;
        while (t) {
            cnt += t * 5;
            res += min(t, additionalTank);
            additionalTank -= min(t, additionalTank);
            t = res / 5;
            res %= 5;
        }
        cnt += res;
        return cnt * 10;
    }
};