//Given an array of integers nums, calculate the pivot index of this array. 
//
// The pivot index is the index where the sum of all the numbers strictly to the
// left of the index is equal to the sum of all the numbers strictly to the index'
//s right. 
//
// If the index is on the left edge of the array, then the left sum is 0 because
// there are no elements to the left. This also applies to the right edge of the a
//rray. 
//
// Return the leftmost pivot index. If no such index exists, return -1. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,7,3,6,5,6]
//Output: 3
//Explanation:
//The pivot index is 3.
//Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
//Right sum = nums[4] + nums[5] = 5 + 6 = 11
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3]
//Output: -1
//Explanation:
//There is no index that satisfies the conditions in the problem statement. 
//
// Example 3: 
//
// 
//Input: nums = [2,1,-1]
//Output: 0
//Explanation:
//The pivot index is 0.
//Left sum = 0 (no elements to the left of index 0)
//Right sum = nums[1] + nums[2] = 1 + -1 = 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -1000 <= nums[i] <= 1000 
// 
// Related Topics Array 
// 👍 1661 👎 315


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: prefix sum
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        if (nums.empty()) return 0;

        int right_sum = 0, left_sum = 0;
        for (int i = 1; i < nums.size(); i++)
            right_sum += nums[i];

        if (right_sum == 0) return 0;

        for (int i = 1; i < nums.size(); i++) {
            left_sum += nums[i - 1];
            right_sum -= nums[i];
            if (left_sum == right_sum) {
                return i;
            }
        }

        return -1;
    }
};

/*
 * solution 2: prefix sum
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixSum(n, 0);

        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        int res = 1e5;
        for (int i = 0; i < n; i++) {
            if (i == 0 && prefixSum[n - 1] - prefixSum[i] == 0 ||
                i == n - 1 && prefixSum[n - 2] == 0 ||
                i > 0 && prefixSum[i - 1] == (prefixSum[n - 1] - prefixSum[i]) ) {

                res = min(res, i);
            }
        }

        return res == 1e5 ? -1 : res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
