/*
solution: double scan
time: O(n)
space: O(1)
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 1;
        while (i >= 1 && nums[i] <= nums[i - 1])
            i--;
        
        // the array decreases monotonously, return the smallest one
        if (i == 0) {
            // sort(nums.begin(), nums.end());
            reverse(nums.begin(), nums.end());
            return;
        }
        
        // because i stops at the highest point
        i--;
        
        // look for a number is larger than current nums[i]. 
        // only a distinct value will exist. 
        // otherwise, the change will happen earlier if there are two largers number.
        int j = nums.size() - 1;
        while (j >= i && nums[i] >= nums[j])
            j--;
        swap(nums[i], nums[j]);
        // sort(nums.begin() + i + 1, nums.end());
        reverse(nums.begin() + i + 1, nums.end());
        return;
    }
};