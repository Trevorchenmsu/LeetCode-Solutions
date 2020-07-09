class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0 || nums.empty()){
            return {-1, -1};
        }
        vector<int> res;
        
        int left_bound = binarySearch(nums, target - 0.5);
        int right_bound = binarySearch(nums, target + 0.5);
        
        if(right_bound == left_bound){
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        
        res.push_back(left_bound);
        res.push_back(right_bound - 1);
        return res;
    }
    
private:
    int binarySearch(vector<int>& nums, double target){
        int start = 0, end = nums.size() - 1;
        while(start <= end){
            int mid = start + (end - start) / 2;
            if(nums[mid] > target){
                end = mid - 1;
            } else if (nums[mid] < target){
                start = mid + 1;
            }
        }
        return start;
    }
};