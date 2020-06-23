class Solution {
public:
    int maxProduct(vector<int>& nums) {
    	if(nums.size() == 0 || nums.empty()) 
            return 0;
        int max_val = nums[0];
        int min_val = nums[0];
        int res = nums[0];
        for(int i = 1; i < nums.size(); ++i){
            int temp = max_val;
            max_val = max(max(max_val * nums[i], min_val * nums[i]), nums[i]);
            min_val = min(min(min_val * nums[i], temp * nums[i]), nums[i]);
            res = max(max_val, res);
        }
        return res;

    }
 };