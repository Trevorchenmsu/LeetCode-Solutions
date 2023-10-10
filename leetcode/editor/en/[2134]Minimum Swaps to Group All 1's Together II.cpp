//A swap is defined as taking two distinct positions in an array and swapping th
//e values in them. 
//
// A circular array is defined as an array where we consider the first element a
//nd the last element to be adjacent. 
//
// Given a binary circular array nums, return the minimum number of swaps requir
//ed to group all 1's present in the array together at any location. 
//
// 
// Example 1: 
//
// 
//Input: nums = [0,1,0,1,1,0,0]
//Output: 1
//Explanation: Here are a few of the ways to group all the 1's together:
//[0,0,1,1,1,0,0] using 1 swap.
//[0,1,1,1,0,0,0] using 1 swap.
//[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
//There is no way to group all 1's together with 0 swaps.
//Thus, the minimum number of swaps required is 1.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,1,1,1,0,0,1,1,0]
//Output: 2
//Explanation: Here are a few of the ways to group all the 1's together:
//[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
//[1,1,1,1,1,0,0,0,0] using 2 swaps.
//There is no way to group all 1's together with 0 or 1 swaps.
//Thus, the minimum number of swaps required is 2.
// 
//
// Example 3: 
//
// 
//Input: nums = [1,1,0,0,1]
//Output: 0
//Explanation: All the 1's are already grouped together due to the circular prop
//erty of the array.
//Thus, the minimum number of swaps required is 0.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// nums[i] is either 0 or 1. 
// 
// 👍 159 👎 3


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sliding window
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int ones = 0, x = 0, onesInWindow = 0, i = 0, n = nums.size();

        // 统计原数组中1的个数
        ones = count(begin(nums), end(nums), 1);

        //遇到循环数组的情况，可以把数组加到该数组的尾部，避免考虑循环的问题
        vector<int> nums2(n * 2);
        for (i = 0; i < n * 2; i++)
            nums2[i] = nums[i % n];

        // 核心idea就是统计1的总个数，为了解决循环问题，原数组拼乘2n大小的新数组
        // 在新数组上遍历，用滑窗找出最大长度1的片段，最后用1的总数减去最大连续1片段就是最小替换次数
        for (i = 0; i < n * 2; i++) {
            // 因为i是索引，i=ones时已经表明i超过了ones个数的最大位置
            // 这里就是滑窗的思想，ones其实就是滑窗大小，当i超出滑窗后，判断左边界是否为1
            // 如果为1，则表示滑窗内1的个数少了1个，所以x--
            if (i >= ones && nums2[i - ones] == 1) x--;
            if (nums2[i] == 1) x++;
            onesInWindow = max(x, onesInWindow);
        }

        return ones - onesInWindow;
    }
};

/*
 * solution 2: sliding window, optimal, template
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int ones = count(nums.begin(), nums.end(), 1);
        int cnt_one = 0, max_one = 0, n = nums.size();
        int left = 0, right = 0;

        //遇到循环数组的情况，可以把数组加到该数组的尾部，避免考虑循环的问题
        vector<int> nums2(n * 2);
        for (int i = 0; i < n * 2; i++)
            nums2[i] = nums[i % n];

        while (right < 2 * n) {
            // 遇到新元素，统计1的个数
            cnt_one += nums2[right++];
            // 不满足滑窗内容，缩短左边界
            if (right - left > ones) {
                // 更新当前1的个数
                cnt_one -= nums2[left++];
            }
            // 更新数组最大连续1的长度
            max_one = max(max_one, cnt_one);
        }

        return ones - max_one;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
