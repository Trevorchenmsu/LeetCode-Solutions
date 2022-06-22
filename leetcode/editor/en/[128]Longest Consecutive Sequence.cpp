//Given an unsorted array of integers nums, return the length of the longest con
//secutive elements sequence. 
//
// You must write an algorithm that runs in O(n) time. 
//
// 
// Example 1: 
//
// 
//Input: nums = [100,4,200,1,3,2]
//Output: 4
//Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Theref
//ore its length is 4.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,3,7,2,5,8,4,6,0,1]
//Output: 9
// 
//
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 105 
// -109 <= nums[i] <= 109 
// 
// Related Topics Array Hash Table Union Find 
// 👍 6688 👎 309


//leetcode submit region begin(Prohibit modification and deletion)
/*
naive思路：
1.排序
2.逐一遍历，看看前后两个元素差值是否为1
3. 滑窗
卡点：
（1）如果不排序，想不到其它的方式可以按顺序考虑的情况；
A: 考虑题目的特点，要找的是连续的元素们，用该元素的加1减1判断是否存在在哈希集中，可以逐渐判定是否
在元素中存在这个元素。
（2）当知道用哈希集，想不到如何处理长度的计算，想用计数器的方式，但是前面计数后如果删掉
了某些元素，会导致后面的计数不正确。
A:不采用计数器，其实本质是滑窗中求双指针长度的方法，一个左指针一个右指针。它们往两边扩展的方式就是
不断从哈希集中删除存在的元素
（3）并查集如何使用？
*/

/*
 * solution: haseset
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        if (nums.empty() || nums.size() == 0) return res;

        unordered_set<int> num_set;

        for (auto num : nums) num_set.insert(num);

        for (auto num : nums)
        {
            int left = num - 1;
            while (num_set.find(left) != num_set.end())
            {
                num_set.erase(left);
                --left;
            }

            int right = num + 1;
            while (num_set.find(right) != num_set.end())
            {
                num_set.erase(right);
                ++right;
            }

            res = max(res, right - left - 1);
        }
        return res;
    }
};


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        res = 0
        if nums is None: return res

        num_set = set(nums)

        for num in nums:
            left = num - 1
            while left in num_set:
                num_set.remove(left)
                left -= 1

            right = num + 1
            while right in num_set:
                num_set.remove(right)
                right += 1

            res = max(res, right - left - 1)

        return res
//leetcode submit region end(Prohibit modification and deletion)
