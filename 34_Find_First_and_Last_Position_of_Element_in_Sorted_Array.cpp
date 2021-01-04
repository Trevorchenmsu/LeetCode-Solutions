/*
Solution 1: brute force
time: O(n), n is the length of the array
space: O(k), k is the number of duplicate elements in the array
*/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        if (nums.empty() || nums.size() == 0)
            return res;
        
        vector<int> index;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target)
                index.push_back(i);
        }
        
        if (!index.empty()) {
            res[0] = index[0];
            res[1] = index[index.size() - 1];
        }
 
        return res;
    }
};


/*
Solution 2: binary search
time: O(logn), n is the length of the array
space: O(1)
*/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        if (nums.empty() || nums.size() == 0)
            return res;
        
        int left, right, mid;
        
        // binary search for the left part
        left = 0, right = nums.size() - 1;
        while (left + 1 < right) {
            mid = (right - left) / 2 + left;
            if (nums[mid] < target)
                left = mid;
            else if (nums[mid] > target) 
                right = mid;
            else 
                right = mid;
        }
        
        if (nums[left] == target)
            res[0] = left;
        else if (nums[right] == target)
            res[0] = right;
        
        
        // binary search for the left part
        left = 0, right = nums.size() - 1;
        while (left + 1 < right) {
            mid = (right - left) / 2 + left;
            if (nums[mid] < target)
                left = mid;
            else if (nums[mid] > target) 
                right = mid;
            else 
                left = mid;
        }
        
        if (nums[right] == target)
            res[1] = right;
        else if (nums[left] == target)
            res[1] = left;
        
        return res;
    }
};

/*
Solution 3: Optimized binary search
time: O(logn), n is the length of the array
space: O(1)
*/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        if (nums.empty() || nums.size() == 0)
            return res;
        
        int left_bound = binarySearch(nums, target - 0.5);
        int right_bound = binarySearch(nums, target + 0.5);
        
        if(right_bound != left_bound){
            res[0] = left_bound;
            res[1] = right_bound - 1;
        }
        
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