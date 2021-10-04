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

        int start = 0, end = m; // 不同于普通二分，这里右边界是m，而不是m-1
        while (start < end) { // 九章模板采用倒是start + 1 < end
            int mid_n1 = start + (end - start + 1) / 2; // 采用end-start+1，目的是得到右段的第一个元素，而不是左段的右边界。
            int mid_n2 = len - mid_n1;

            if (nums1[mid_n1 - 1] > nums2[mid_n2]) // 只需要判断N1左段最大值是否小于等于N2右端最小值
                end = mid_n1 - 1; //这里会限制一个误区，认为让指针左移，但根据二分法，应该是右边界左移
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
 * solution 2: divide and conquer
 * time: O(log(m + n))
 * space: O(log(m + n))
 * */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        // 如果m+n为奇数，则left和right相等。如果为偶数，则left和right错开。这样可以应对奇偶长度的m+n
        int left = (m + n + 1) / 2, right = (m + n + 2) / 2;

        //分治法的思路相当于在n1和n2合成的大数组中，查找第k个数，这个k就是上面的left或者right
        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    }

    int findKth(vector<int> &nums1, int i, vector<int> &nums2, int j, int k) {
        //如果n1的起始位置大于等于其数组长度时，则其所有数字已经被淘汰了
        if (i >= nums1.size())
            return nums2[j + k - 1];

        //如果n2的起始位置大于等于其数组长度时，则其所有数字已经被淘汰了
        if (j >= nums2.size())
            return nums1[i + k - 1];

        // 如果k=1，表示我们要查找第一个数，那只能时n1或者n2的起点
        if (k == 1)
            return min(nums1[i], nums2[j]);

        /*
         *因为需要在两个有序数组中找到第K个元素，为了加快搜索的速度，可以使用二分法，那么对谁二分呢，数组么？
         *其实要对K二分，意思是需要分别在nums1和nums2中查找第K/2个元素。为什么可以这样?假如把n1和n2各自分为两段，左段肯定都是较小的数，
         * 即便我们要合成整个大数组，那也是n1的左段和n2的左段合成较小的大数组左段，右段同理。例如n1=[1,2,3,4],n2=[5,6,7,8]，我想找第4个数，
         *
         *
         * */

        int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;

        if (midVal1 < midVal2)
            return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
        else
            return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
    }
};





//leetcode submit region end(Prohibit modification and deletion)
