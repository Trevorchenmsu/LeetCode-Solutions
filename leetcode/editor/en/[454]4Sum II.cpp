//Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, retu
//rn the number of tuples (i, j, k, l) such that: 
//
// 
// 0 <= i, j, k, l < n 
// nums1[i] + nums2[j] + nums3[k] + nums[l] == 0 
// 
//
// 
// Example 1: 
//
// 
//Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
//Output: 2
//Explanation:
//The two tuples are:
//1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1)
// + 2 = 0
//2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1)
// + 0 = 0
// 
//
// Example 2: 
//
// 
//Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// n == nums1.length 
// n == nums2.length 
// n == nums3.length 
// n == nums4.length 
// 1 <= n <= 200 
// -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228 
// 
// Related Topics Hash Table Binary Search 
// 👍 1912 👎 84


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> cnt;
        int res = 0, n = nums1.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cnt[nums1[i] + nums2[j]]++;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res += cnt[-nums3[i] - nums4[j]];
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
