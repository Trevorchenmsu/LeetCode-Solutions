class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
    	// edge case
    	if(nums.empty() || nums.size() == 0){
    		return -1;
    	}

    	// binary search
    	int start = 0, end = nums.size() - 1;

    	if(target < nums[start]){
    		return start;
    	}
    	if(traget > nums[end]){
    		return end;
    	}

    	while(start + 1 < end){
    		int mid = start + (end - start) / 2;
    		if(nums[mid] == target){
    			return mid;
    		} else if(nums[mid] > target){
    			end = mid;
    		} else {
    			start = mid;
    		}
    	}

    	if(nums[start] == target){
    		return start;
    	}
    	if(nums[end] ==  target){
    		return end;
    	}
    	return start + 1;

    }
};