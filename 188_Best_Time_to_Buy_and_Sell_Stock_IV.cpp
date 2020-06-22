class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
    	int len = prices.size();
    	if(prices.empty() || len == 0)
    		return 0;
    	if(k >= len / 2)
    		return helper(prices);

    	vector<int> dp(k + 1, 0);
    	vector<int> min_val(k + 1, prices[0]);

    	for(int i = 1; i < len; ++i){
    		for(int j = 1; j <= k; ++j){
    			min_val[j] = min(min_val[j], prices[i] - dp[j - 1]);
    			dp[j] = max(dp[j], prices[i] - min_val[j]);
    		}
    	}
    	return dp[k];
    }

private:
	int helper(vector<int>& prices, int res = 0){
		for(int i = 1; i < prices.size(); ++i){
			res += max(0, prices[i] - prices[i - 1]);
		}
		return res;
	}
};