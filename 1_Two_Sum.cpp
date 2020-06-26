// Solution 1: Hash map

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	if(nums.size() == 0 || nums.empty()) 
			return {};

		vector<int> res;

		unordered_map<int, int> map;

		for(int i = 0; i < nums.size(); ++i){
			if(map.count(target - nums[i]))
				res.emplace_back(i);
				res.emplace_back(map[target - nums[i]]);
				break;
			else{
				map[nums[i]] = i;
			}
		}
		return res;
    }
};

// Solution 2: Two pointer

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	if(nums.size() == 0 || nums.empty()) 
			return {};

		vector<int> res;
        vector<int> copy = nums;
		sort(nums.begin(), nums.end());
		int left = 0, right = nums.size() - 1;
		
		for(int i = 0; i < nums.size(); ++i){
			int sum = nums[left] + nums[right];
			if(sum > target){
				right--;
			} else if (sum < target){
				left++;
			} else{
                break;
			}
		}
        
        for(int i = 0; i < copy.size(); ++i){
            if(copy[i] == nums[left] || copy[i] == nums[right]){
                res.push_back(i);
            }
        }
        
		return res;
    }
};
