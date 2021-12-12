//Implement next permutation, which rearranges numbers into the lexicographicall
//y next greater permutation of numbers. 
//
// If such an arrangement is not possible, it must rearrange it as the lowest po
//ssible order (i.e., sorted in ascending order). 
//
// The replacement must be in place and use only constant extra memory. 
//
// 
// Example 1: 
// Input: nums = [1,2,3]
//Output: [1,3,2]
// Example 2: 
// Input: nums = [3,2,1]
//Output: [1,2,3]
// Example 3: 
// Input: nums = [1,1,5]
//Output: [1,5,1]
// Example 4: 
// Input: nums = [1]
//Output: [1]
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 100 
// 0 <= nums[i] <= 100 
// 
// Related Topics Array Two Pointers 
// 👍 6669 👎 2199


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: math, implementation
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) {
            return;
        }

        /*
         * 当考虑数组的任意长度右部时，从尾到头遍历这部分时，只能是逐渐递增或者逐渐递减（相等的情况可忽略）。
         * （1）如果从右到左是递减的情况，我们只需要交换最后两个元素，例如[1,2,3,4,5]，只能交换4和5变成[1,2,3,5,4]。
         * 因为交换其他元素都会产生更大的排列，所以不是下一个相邻的全排列。从这可以观察出，从右到左遍历时，
         * 我们找到了第一个下降的元素进行交换，但是这里的规律还不够明显。
         * （2）如果从右到左时递减的情况，例如[1,2,5,4,3]，我们要查找第一个下降的元素，即2。为什么要找下降点？
         * 因为我们想找下一个相邻的更大的排列，正常思路肯定是优先交换末端的某些元素来产生一个更大的数，如果考虑左端，尽管能够
         * 产生更大的排列，但是肯定不是相邻的。而查找第一个顶峰后下降的点，首先可以保证这两个相邻点一定可以交换得到更大的数。其次
         * 我们在顶峰更靠右的位置找出比顶峰小但比下降点大的数来和下降点更换。如果没有这样的点，就拿顶峰来交换，也就是上述（1）中的情况。那么，
         * 接下来的问题就是如何找出下一个更大的排列，同时还得是相邻的排列。按照上述，我们只需要从右到左（不小于已经到的下降点），找
         * 到第一个大于下降点的进行交换即可。但是这个交换后仍然不一定是相邻的排列。因此，我们需要对下降点后面的一部分进行reverse。
         * 因为我们之前查找的是从右到左的上升数据，当下降点换到一个大数后，后面一段的数据将递增改为递减，就可以得到最相邻的更大排列。
         * 例如，上述例子交换后得到[1,3,5,4,2]，再reverse一下[1,3,2,4,5]，13245明显大于12543，且最相邻的下一个排列。
         * */

        /*
         * 核心思想：
         * （1）找下降点；
         * （2）找不到下降点就返回升序排序；
         * （3）找到下降点后在右段找比第一个比下降点大的数，然后交换；
         * （4）交换后，对下降点的右段进行翻转。因为之前从右到左是升序的，翻转后从右到左为降序，排列更小。
         * */
        int i = nums.size() - 1;
        while (i >= 1 && nums[i] <= nums[i - 1]) {
            i--;
        }

        // 如果数据是从左到右递减，表示排列已经达到最大值，直接reverse返回最小排列即可
        if (i == 0) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // 因为上述循环的终止位置是在顶峰，所以需要i自减到下降点
        i--;

        // 从右部继续查找另一个比下降点更大的第一个数
        int j = nums.size() - 1;
        while (j >= i && nums[i] >= nums[j]) {
            j--;
        }

        // 交换两个数，reverse后得到最相邻的排列
        swap(nums[j], nums[i]);
        reverse(nums.begin() + i + 1, nums.end());
    }
};
//leetcode submit region end(Prohibit modification and deletion)
