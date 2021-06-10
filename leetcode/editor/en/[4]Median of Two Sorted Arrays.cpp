//Given two sorted arrays nums1 and nums2 of size m and n respectively, return t
//he median of the two sorted arrays. 
//
// 
// Example 1: 
//
// 
//Input: nums1 = [1,3], nums2 = [2]
//Output: 2.00000
//Explanation: merged array = [1,2,3] and median is 2.
// 
//
// Example 2: 
//
// 
//Input: nums1 = [1,2], nums2 = [3,4]
//Output: 2.50000
//Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
// 
//
// Example 3: 
//
// 
//Input: nums1 = [0,0], nums2 = [0,0]
//Output: 0.00000
// 
//
// Example 4: 
//
// 
//Input: nums1 = [], nums2 = [1]
//Output: 1.00000
// 
//
// Example 5: 
//
// 
//Input: nums1 = [2], nums2 = []
//Output: 2.00000
// 
//
// 
// Constraints: 
//
// 
// nums1.length == m 
// nums2.length == n 
// 0 <= m <= 1000 
// 0 <= n <= 1000 
// 1 <= m + n <= 2000 
// -106 <= nums1[i], nums2[i] <= 106 
// 
//
// 
//Follow up: The overall run time complexity should be O(log (m+n)). Related Top
//ics Array Binary Search Divide and Conquer 
// 👍 9797 👎 1500


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search
 * time: O(log(min(m,n)))
 * space: O(1)
 * */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        int m = nums1.size(), n = nums2.size();
        int len = (m + n + 1) / 2;

        int start = 0, end = m;
        while (start < end) {
            int mid_n1 = start + (end - start + 1) / 2;
            int mid_n2 = len - mid_n1;

            if (nums1[mid_n1 - 1] > nums2[mid_n2])
                end = mid_n1 - 1;
            else
                start = mid_n1;
        }

        int mid_n1 = start;
        int mid_n2 = len - mid_n1;

        // boundary conditions
        int left1 = mid_n1 == 0 ? INT_MIN : nums1[mid_n1 - 1];
        int right1 = mid_n1 == m ? INT_MAX : nums1[mid_n1];
        int left2 = mid_n2 == 0 ? INT_MIN : nums2[mid_n2 - 1];
        int right2 = mid_n2 == n ? INT_MAX : nums2[mid_n2];

        int leftMax = max(left1, left2);
        int rightMin = min(right1, right2);

        return (m + n) % 2 == 0 ? (leftMax + rightMin) / 2.0 : leftMax;
    }
};


/*
 * solution 2: divide and conquery
 * time: O(log(m + n))
 * space: O(log(m + n))
 * */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int left = (m + n + 1) / 2, right = (m + n + 2) / 2;

        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    }

    int findKth(vector<int> &nums1, int i, vector<int> &nums2, int j, int k) {
        if (i >= nums1.size())
            return nums2[j + k - 1];

        if (j >= nums2.size())
            return nums1[i + k - 1];

        if (k == 1)
            return min(nums1[i], nums2[j]);

        int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;

        if (midVal1 < midVal2)
            return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
        else
            return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
    }
};


//leetcode submit region end(Prohibit modification and deletion)
