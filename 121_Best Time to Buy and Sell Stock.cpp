class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 0) return 0;
        int min_val = prices[0];
        int profit = 0;
        for (int price : prices) {
            min_val = min(min_val, price);
            profit = max(profit, price - min_val);
        }
        return profit;
    }
};