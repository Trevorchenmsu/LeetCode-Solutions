//Given a binary array data, return the minimum number of swaps required to grou
//p all 1’s present in the array together in any place in the array. 
//
// 
// Example 1: 
//
// 
//Input: data = [1,0,1,0,1]
//Output: 1
//Explanation: There are 3 ways to group all 1's together:
//[1,1,1,0,0] using 1 swap.
//[0,1,1,1,0] using 2 swaps.
//[0,0,1,1,1] using 1 swap.
//The minimum is 1.
// 
//
// Example 2: 
//
// 
//Input: data = [0,0,0,1,0]
//Output: 0
//Explanation: Since there is only one 1 in the array, no swaps are needed.
// 
//
// Example 3: 
//
// 
//Input: data = [1,0,1,0,1,0,0,1,1,0,1]
//Output: 3
//Explanation: One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1
//].
// 
//
// 
// Constraints: 
//
// 
// 1 <= data.length <= 105 
// data[i] is either 0 or 1. 
// 
// Related Topics Array Sliding Window 
// 👍 619 👎 6


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution: sliding window
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int minSwaps(vector<int>& data) {
        int ones = count(data.begin(), data.end(), 1);
        int cnt_one = 0, max_one = 0, n = data.size();
        int left = 0, right = 0;

        while (right < n) {
            // 遇到新元素，统计1的个数
            cnt_one += data[right++];
            // 不满足滑窗内容，缩短左边界
            if (right - left > ones) {
                // 更新当前1的个数
                cnt_one -= data[left++];
            }
            // 更新数组最大连续1的长度
            max_one = max(max_one, cnt_one);
        }

        return ones - max_one;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
