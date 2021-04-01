//Given two integer arrays nums1 and nums2, return an array of their intersectio
//n. Each element in the result must appear as many times as it shows in both arra
//ys and you may return the result in any order. 
//
// 
// Example 1: 
//
// 
//Input: nums1 = [1,2,2,1], nums2 = [2,2]
//Output: [2,2]
// 
//
// Example 2: 
//
// 
//Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
//Output: [4,9]
//Explanation: [9,4] is also accepted.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums1.length, nums2.length <= 1000 
// 0 <= nums1[i], nums2[i] <= 1000 
// 
//
// 
// Follow up: 
//
// 
// What if the given array is already sorted? How would you optimize your algori
//thm? 
// What if nums1's size is small compared to nums2's size? Which algorithm is be
//tter? 
// What if elements of nums2 are stored on disk, and the memory is limited such 
//that you cannot load all elements into the memory at once? 
// 
// Related Topics Hash Table Two Pointers Binary Search Sort 
// 👍 2123 👎 515


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers + sort
 * time: O(max(mlogm,nlogn)), m is the size of array 1, n is the size of array 2
 * space: O(max(logm, logn))
 * */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        if (nums1.empty() || nums2.empty())
            return res;

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int m = nums1.size(), n = nums2.size();
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] == nums2[j]) {
                res.push_back(nums1[i]);
                i++, j++;
            }
            else if (nums1[i] > nums2[j]) j++;
            else i++;
        }

        return res;
    }
};


/*
 * solution 2: hash table
 * time: O(max(m, n)), m is the size of nums1, n is the size of nums2
 * space: O(min(m, n)
 * */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        if (nums1.empty() || nums2.empty())
            return res;

        if (nums1.size() > nums2.size())
            return intersect(nums2, nums1);

        unordered_map<int, int> m1;

        for (auto &num : nums1)
            m1[num]++;

        for (auto &num : nums2) {
            if (!m1.count(num))
                continue;

            if (m1[num] > 0) {
                res.push_back(num);
                m1[num]--;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
