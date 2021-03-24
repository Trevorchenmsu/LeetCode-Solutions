//Given an integer array nums of size n, return the minimum number of moves requ
//ired to make all array elements equal. 
//
// In one move, you can increment n - 1 elements of the array by 1. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3]
//Output: 3
//Explanation: Only three moves are needed (remember each move increments two el
//ements):
//[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
// 
//
// Example 2: 
//
// 
//Input: nums = [1,1,1]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= nums.length <= 104 
// -109 <= nums[i] <= 109 
// 
// Related Topics Math 
// 👍 777 👎 1126


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 0; i--) {
            res += nums[i] - nums[0];
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
