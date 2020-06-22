class Solution {
public:
    int maxSubArray(vector<int>& nums) {
    	if(nums.size() == 0 || nums.empty()) return 0;
        int max_val = INT_MIN, sum = 0, minSum = 0;
        for(int num : nums){
        	sum += num;
        	max_val = max(max_val, sum - minSum);
        	minSum = min(minSum, sum);
        }
        return max;
    }
};