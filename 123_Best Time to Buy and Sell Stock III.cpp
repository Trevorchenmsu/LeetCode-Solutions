// solution 1: state machine

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 0) return 0;
        int sell1 = 0, sell2 = 0;
        int buy1 = INT_MIN, buy2 = INT_MIN;

        for (int price : prices) {
            sell2 = max(sell2, price + buy2);
            buy2 = max(buy2, sell1 - price);
            sell1 = max(sell1, price + buy1);
            buy1 = max(buy1, -price);
        }
        return sell2;
    }
};

// solution 2: DP
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 0) return 0;
        vector<int> dp(3, 0);
        vector<int> min_val(3, 0);
        for (int i = 1; i < prices.size(); ++i) {
            for (int k = 1; k <= 2; ++k) {
                min_val[k] = min(min_val[k], prices[i] - dp[k - 1]);
                dp[k] = max(dp[k], prices[i] - min_val[k]);
            }
        }
        return dp[2];
    }
};