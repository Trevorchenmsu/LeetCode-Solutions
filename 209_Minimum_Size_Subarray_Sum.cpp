class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
    	if(nums.size() == 0 || nums.empty()){
    		return 0;
    	}

    	int res = INT_MAX;  	
    	int left = 0;
    	int sum = 0;

    	for(int i = 0; i < nums.size(); ++i){
    		sum += nums[i];
    		while(left <= i && sum >= s){
    			res = min(res, i - left + 1);
                sum -= nums[left++];
    		}
    	}
    	return res == INT_MAX ? 0 : res;
    }

};


     
        