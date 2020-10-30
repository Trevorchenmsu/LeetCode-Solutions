/*
solution 1
*/
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        if (piles.empty() || piles.size() == 0)
            return false;
        
        // Computing the total sum
        int sum = 0;
        for(auto& pile :piles) { 
            sum += pile; 
        }
        
        // Point i and j at beginning and end of array
        int score = 0;
        // Going to go over size/2 iterations
        for(int i = 0, j = piles.size() - 1; i < (piles.size())/2; ++i,  --j) {
            score += max((piles[i] + min(piles[i + 1, j - 1], piles[i + 2, j])),
                         (piles[j] + min(piles[i + 1, j - 1], piles[i, j - 2])));
        }

        return (score > (sum) / 2);
    }
};

/*
solution 2
*/
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        if (piles.size() == 0) {
            return false;
        }
        
        int N = piles.size();

        vector<vector<int>> dp(N+2, vector<int> (N+2));

        for (int size = 1; size <= N; ++size)
            for (int i = 0, j = size - 1; j < N; ++i, ++j) {
                int parity = (j + i + N) % 2;  // j - i - N; but +x = -x (mod 2)
                if (parity == 1)
                    dp[i+1][j+1] = max(piles[i] + dp[i+2][j+1], piles[j] + dp[i+1][j]);
                else
                    dp[i+1][j+1] = min(-piles[i] + dp[i+2][j+1], -piles[j] + dp[i+1][j]);
            }

        return dp[1][N] > 0;
    }
};