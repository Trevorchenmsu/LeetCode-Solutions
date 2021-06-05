//Given an array of integers nums, find the maximum length of a subarray where t
//he product of all its elements is positive. 
//
// A subarray of an array is a consecutive sequence of zero or more values taken
// out of that array. 
//
// Return the maximum length of a subarray with positive product. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,-2,-3,4]
//Output: 4
//Explanation: The array nums already has a positive product of 24.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,1,-2,-3,-4]
//Output: 3
//Explanation: The longest subarray with positive product is [1,-2,-3] which has
// a product of 6.
//Notice that we cannot include 0 in the subarray since that'll make the product
// 0 which is not positive. 
//
// Example 3: 
//
// 
//Input: nums = [-1,-2,-3,0,1]
//Output: 2
//Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].
//
// 
//
// Example 4: 
//
// 
//Input: nums = [-1,2]
//Output: 1
// 
//
// Example 5: 
//
// 
//Input: nums = [1,2,3,5,-6,4,0,10]
//Output: 4
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 10^5 
// -10^9 <= nums[i] <= 10^9 
// 
// Related Topics Greedy 
// 👍 423 👎 7


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int ret = 0;

        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i]==0) continue;
            int j = i;
            int count = 0;
            int firstNeg = -1;

            while (j<nums.size() && nums[j]!=0)
            {
                count += (nums[j]<0);
                if (count % 2 ==0)
                    ret = max(ret, j-i+1);
                else if (firstNeg!=-1)
                    ret = max(ret, j-firstNeg);

                if (firstNeg==-1 && nums[j]<0)
                    firstNeg = j;
                j++;
            }
            i = j;
        }
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
