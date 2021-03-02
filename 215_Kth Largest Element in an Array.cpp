/*
Solution: quick select
time: O(n) for average, O(n^2) in the worst case. n + n/2 + n/4  +… + 1 = O(n)
space: O(1)
*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - (k - 1));
    }
    
    int quickSelect(vector<int> &nums, int start, int end, int k) {
        if (start == end) return nums[start];
        
        // partition
        int left = start, right = end;
        int pivot = nums[(start + end) / 2];
        while (left <= right) {
            while (left <= right && nums[left] < pivot) left++;
            while (left <= right && nums[right] > pivot) right--;
            if (left <= right) swap(nums[left++], nums[right--]);
        }
        
        if (start + k - 1 <= right) {
            return quickSelect(nums, start, right, k);
        }
        
        if (start + k - 1 >= left) {
            return quickSelect(nums, left, end, k - (left- start));
        }
        
        return nums[right + 1];
    }
};
