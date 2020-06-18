class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int cut1 = 0;
        int cut2 = 0;
        int cutL = 0;
        int cutR = nums1.size();
        int len = nums1.size() + nums2.size();

        while (cut1 <= nums1.size()) {
            cut1 = cutL + (cutR - cutL) / 2;
            cut2 = len / 2 - cut1;
            double L1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            double L2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
            double R1 = cut1 == nums1.size() ? INT_MAX : nums1[cut1];
            double R2 = cut2 == nums2.size() ? INT_MAX : nums2[cut2];
            if (L1 > R2) {
                cutR = cut1 - 1;
            }
            else if (L2 > R1) {
                cutL = cut1 + 1;
            }
            else {
                if (len % 2 == 0) {
                    L1 = max(L1, L2);
                    R1 = min(R1, R2);
                    return (L1 + R1) / 2 
                }
                else {
                    return min(R1, R2);
                }
            }
        }
        return -1;
    }
};