//Given an integer array nums and an integer k, return the kth largest element i
//n the array. 
//
// Note that it is the kth largest element in the sorted order, not the kth dist
//inct element. 
//
// 
// Example 1: 
// Input: nums = [3,2,1,5,6,4], k = 2
//Output: 5
// Example 2: 
// Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
//Output: 4
// 
// 
// Constraints: 
//
// 
// 1 <= k <= nums.length <= 104 
// -104 <= nums[i] <= 104 
// 
// Related Topics Divide and Conquer Heap 
// 👍 5520 👎 354


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: quick select
 * time: O(n)
 * space: O(logn)
 * */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - (k - 1));
    }

    int quickSelect(vector<int> &nums, int start, int end, int k) {
        if (start == end) return nums[start];

        // partition
        int i = start, j = end;
        int mid = i + (j - i) / 2;
        int pivot = nums[mid];

        while (i <= j) {
            while (i <= j && nums[i] < pivot)
                i++;
            while (i <= j && nums[j] > pivot)
                j--;

            if (i <= j)
                swap(nums[i++], nums[j--]);
        }

        // divide and conquer
        if (start + k - 1 <= j)
            return quickSelect(nums, start, j, k); // left part
        if (start + k - 1 >= i)
            return quickSelect(nums, i, end, k - (i - start));

        return nums[j + 1];
    }

};
//leetcode submit region end(Prohibit modification and deletion)
