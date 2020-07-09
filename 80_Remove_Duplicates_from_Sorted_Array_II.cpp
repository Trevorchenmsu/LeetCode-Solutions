class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
    	if(nums.empty() || nums.size() == 0){
    		return 0;
    	}
    	
    	int idx = 0;
    	for(int num : nums){
    		if(idx < 2 || num > nums[idx - 2]){
    			nums[idx++] = num;
    		}
    	}
    	return idx;
    }
};