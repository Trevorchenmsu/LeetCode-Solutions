     int sLen = s.size(), pLen = p.size();
//         // dp[i][j] represents the matching state of i characters in s and j characters in p
//         vector<vector<bool>> dp(sLen + 1, vector<bool> (pLen + 1));
//         dp[0][0] = true; // both s and p are empty
        
//         // s is empty
//         for (int j = 1; j <= plen; ++j) {
//             if (p[j - 1] == '*')
//                 dp[0][j] = dp[0][j - 1];
//         }