class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
    	// edge case
    	if(nums.empty() || nums.size() == 0){
    		return {};
    	}

    	vector<int> res;
    	// find potential two elements
    	int num1 = nums[0], num2 = nums[0];
    	int count1 = 0, count2 = 0;
    	for(int num : nums){  		
    		if(num == num1){
    			count1++;
    		} else if (num == num2){
    			count2++;
    		} else if(count1 == 0){
    			num1 = num;
    			count1++;
    		} else if(count2 == 0){
    			num2 = num;
    			count2++;
    		} else{
    			count1--;
    			count2--;
    		}
    	}

    	// compute the number of two elements in the array
    	count1 = 0,  count2 = 0;
    	for(int num : nums){
    		if(num == num1){
    			count1++;
    		} else if(num == num2){
    			count2++;
    		}

    	}

    	// determin whether the element meets the requirement
    	if(count1 > nums.size() / 3 ){
    		res.push_back(num1);
    	}
    	if(count2 > nums.size() / 3){
    		res.push_back(num2);
    	}

    	// return final results
    	return res;
    }
};
