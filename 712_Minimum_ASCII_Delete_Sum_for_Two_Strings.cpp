class Solution {
public:
    int minimumDeleteSum(string s1, string s2)
    {
        int len1 = s1.length();
        int len2 = s2.length();

        int dp[len1 + 1][len2 + 1];
        memset(dp,0, sizeof(dp));

        for (int i = 1; i <= len1; ++i)
            for (int j = 1; j <= len2; ++j)
            {
                if(s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
                else
                    dp[i][j] = max(dp[i - 1][j],dp[i][j - 1]);
            }

        int sum = 0;
        for (int i = 0; i < len1; ++i)
            sum += s1[i];
        for (int i = 0; i < len2; ++i)
            sum += s2[i];
        return sum - 2 * dp[len1][len2];
    }
};