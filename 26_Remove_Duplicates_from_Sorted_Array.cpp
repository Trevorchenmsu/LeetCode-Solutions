class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
    	// edge case
    	if(nums.empty() || nums.size() == 0){
    		return 0;
    	}

    	// two pointers
    	int left = 1;
    	for(int i = 1; i < nums.size(); ++i){
    		if(nums[i] > nums[i - 1]){
    			nums[left++] = nums[i];
    		}
    	}

    	// return results
    	return left;

    }
};
