//Given a binary array nums and an integer goal, return the number of non-empty 
//subarrays with a sum goal. 
//
// A subarray is a contiguous part of the array. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,0,1,0,1], goal = 2
//Output: 4
//Explanation: The 4 subarrays are bolded and underlined below:
//[1,0,1,0,1]
//[1,0,1,0,1]
//[1,0,1,0,1]
//[1,0,1,0,1]
// 
//
// Example 2: 
//
// 
//Input: nums = [0,0,0,0,0], goal = 0
//Output: 15
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 3 * 104 
// nums[i] is either 0 or 1. 
// 0 <= goal <= nums.length 
// 
// Related Topics Hash Table Two Pointers 
// 👍 851 👎 35


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        unordered_map<int,int>Map;
        Map[0] = 1;
        int sum = 0, ret = 0;
        for (int i=0; i<A.size(); i++)
        {
            sum += A[i];
            if (Map.find(sum-S)!=Map.end())
                ret+=Map[sum-S];
            Map[sum]+=1;
        }
        return ret;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
