// solution 1
class Solution {
public:
    int search(vector<int>& nums, int target) {
    	// corner case
    	if(nums.empty() || nums.size() == 0){
    		return -1;
    	}

    	// binary search
    	int start = 0, end = nums.size() - 1;
    	while(start + 1 < end){
    		int mid = start + (end - start) / 2;
    		if(nums[mid] > nums[start]){
    			if(nums[mid] > target){
    				if(target >= nums[start]){
    					end = mid;
    				} else {
						start = mid;
    				}
    			} else {
    				start = mid;
    			} 
    		} else if(nums[mid] < nums[start]){
    			if(nums[mid] < target){
    				if(target >= nums[start]){
    					end = mid;
    				} else{
    					start = mid;
    				}
    			} else {
    				end = mid;
    			} 
    		}
    	}

    	if(nums[start] == target){
    		return start;
    	}

    	if(nums[end] == target){
    		return end;
    	}

    	return -1;

    }
};

/*
time : O(n)
space: O(1)
*/

