/*
solution: sliding window
time: O(k), we only traverse k length
space: O(1), no extra space
*/
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int res = 0; 
        if (cardPoints.empty() || cardPoints.size() == 0)
            return res;
        
        int sum = 0, n = cardPoints.size();
        
        for (int i = 0; i < k; ++i) {
            sum += cardPoints[i];
        }
        res = sum;
        
        for (int i = 1; i <= k; ++i) {
            sum += cardPoints[n - i] - cardPoints[k - i];
            res = max(res, sum);
        }
        
        return res;
    }
};
