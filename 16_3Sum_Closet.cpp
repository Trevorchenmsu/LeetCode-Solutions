class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
    	int min_val = INT_MAX;
    	sort(nums.begin(), nums.end());
    	for(int i = 0; i < nums.size(); ++i){
    		int left = i + 1, right = nums.size() - 1;
    		while(left < right){
    			int sum = nums[i] + nums[left] + nums[right];
    			min_val = abs(sum - target) < abs(min_val) ? target - sum: min_val;
    			if(sum >= target){
    				right--;
    			} else {
    				left++;
    			} 
    		}
    		if(min_val == 0)
    			break;
    	}

    	return target - min_val;
    }
};