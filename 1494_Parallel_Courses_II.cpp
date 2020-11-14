class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<int> prereq(n);
        for (const auto& dep: dependencies) {
            prereq[dep[1] - 1] |= (1 << (dep[0] - 1));
        }
        
        vector<int> set_prereq(1 << n), valid(1 << n);
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) <= k) {
                for (int i = 0; i < n; ++i) {
                    if (mask & (1 << i)) {
                        set_prereq[mask] |= prereq[i];
                    }
                }
                valid[mask] = ((set_prereq[mask] & mask) == 0);
            }
        }
        
        vector<int> dp(1 << n, INT_MAX / 2);
        dp[0] = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int subset = mask; subset; subset = (subset - 1) & mask) {
                if (valid[subset] && ((mask & set_prereq[subset]) == set_prereq[subset])) {
                    dp[mask] = min(dp[mask], dp[mask ^ subset] + 1);
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};
