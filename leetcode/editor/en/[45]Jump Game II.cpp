//Given an array of non-negative integers nums, you are initially positioned at 
//the first index of the array. 
//
// Each element in the array represents your maximum jump length at that positio
//n. 
//
// Your goal is to reach the last index in the minimum number of jumps. 
//
// You can assume that you can always reach the last index. 
//
// 
// Example 1: 
//
// 
//Input: nums = [2,3,1,1,4]
//Output: 2
//Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 
//step from index 0 to 1, then 3 steps to the last index.
// 
//
// Example 2: 
//
// 
//Input: nums = [2,3,0,1,4]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// 0 <= nums[i] <= 105 
// 
// Related Topics Array Greedy 
// 👍 4381 👎 187


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs
 * time: O(n) ?
 * space: O(1)
 * */
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int start = 0, end = 0,  step = 0;
        if (n == 1) return 0;

        while (start <= end) {
            int start_old = start;
            int end_old = end;
            for (int i = start_old; i <= end_old; i++) {
                end = max(end, i + nums[i]);

                if (end >= n - 1)
                    return step + 1;
            }
            step++;
            start = end_old + 1;
        }

        return 0;
    }
};


/*
 * solution 2: greedy
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int jump(vector<int>& nums) {
        int res = 0, preMax = 0, curMax = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > preMax) {
                preMax = curMax;
                res++;
            }
            curMax = max(curMax, nums[i] + i);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
