/*
solution 1: binary search + array partition
time: O(log(min(m, n)))
space: O(1)
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // prefer to determine the cut in an array with shorter length
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        
        int m = nums1.size(), n = nums2.size();
        int len = (m + n + 1) / 2;
        int left = 0, right = m;
        int median_left, median_right;
        // binary search
        while (left < right) {
            // i represents the first index in the right part of nums1
            // i also represents the number of elements in the left part of nums1
            int i = left + (right - left + 1) / 2;
            // j represents the first index in the right part of nums2
            // j also represents the number of elements in the left part of nums2, so i + j = len
            int j = len - i;
            
            if (nums1[i - 1] > nums2[j]) {
                right = i - 1; // search in [0, i - 1]
            } else left = i;  // search in [i, m]
        }
                
        int i = left;
        int j = len - i;
        
        // i=0 means there is no elements in the left part of nums1, so use INT_MIN to avoid it being selected
        int num1LeftMax = (i == 0 ? INT_MIN : nums1[i - 1]); 
        // i=m means there is no elements in the right part of nums1, so use INT_MAX to avoid it being selected
        int num1RightMin = (i == m ? INT_MAX : nums1[i]);
        // same reasons as above for nums2
        int num2LeftMax = (j == 0 ? INT_MIN :  nums2[j - 1]);
        int nums2RightMin = (j == n ? INT_MAX : nums2[j]);
        
        median_left = max(num1LeftMax, num2LeftMax);
        median_right = min(num1RightMin, nums2RightMin);
        
        return (m + n) % 2 == 0 ? (median_left + median_right) / 2.0 : median_left;
    }
};