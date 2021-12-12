//Given an integer array arr and an integer difference, return the length of the
// longest subsequence in arr which is an arithmetic sequence such that the differ
//ence between adjacent elements in the subsequence equals difference. 
//
// A subsequence is a sequence that can be derived from arr by deleting some or 
//no elements without changing the order of the remaining elements. 
//
// 
// Example 1: 
//
// 
//Input: arr = [1,2,3,4], difference = 1
//Output: 4
//Explanation: The longest arithmetic subsequence is [1,2,3,4]. 
//
// Example 2: 
//
// 
//Input: arr = [1,3,5,7], difference = 1
//Output: 1
//Explanation: The longest arithmetic subsequence is any single element.
// 
//
// Example 3: 
//
// 
//Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
//Output: 4
//Explanation: The longest arithmetic subsequence is [7,5,3,1].
// 
//
// 
// Constraints: 
//
// 
// 1 <= arr.length <= 105 
// -104 <= arr[i], difference <= 104 
// 
// Related Topics Array Hash Table Dynamic Programming 
// 👍 720 👎 34


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dp
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        // sanity check
        int res = 0;
        int n = arr.size();
        vector<int> dp(n);
        dp[0] = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] - arr[j] == difference) {
                    dp[i] = dp[j] + 1;
                }
                dp[i] = max(dp[i], 1);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

/*
* solution 2: hash table
* time: O(n)
* space: O(n)
* */
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int res = 0;
        unordered_map<int, int> nums_map;
        /* 因为解法1中的第二轮for遍历中遍历的那些元素大部分是不满足两数之差等于diff的，那我们何必遍历那么多次？
           我们只需要建立哈希表，每次遍历时，减去这个差值，看看得到的值是否在哈希表中，就知道前面是否已经出现过了
           这种方式也可以保证一直是往前考虑的。
        */
        for (const auto& num : arr) {
            nums_map[num] = 1 + nums_map[num - difference];
            res = max(res, nums_map[num]);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
