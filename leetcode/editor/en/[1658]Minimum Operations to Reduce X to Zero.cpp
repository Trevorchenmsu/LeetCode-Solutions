//You are given an integer array nums and an integer x. In one operation, you ca
//n either remove the leftmost or the rightmost element from the array nums and su
//btract its value from x. Note that this modifies the array for future operations
//. 
//
// Return the minimum number of operations to reduce x to exactly 0 if it's poss
//ible, otherwise, return -1. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,1,4,2,3], x = 5
//Output: 2
//Explanation: The optimal solution is to remove the last two elements to reduce
// x to zero.
// 
//
// Example 2: 
//
// 
//Input: nums = [5,6,7,8,9], x = 4
//Output: -1
// 
//
// Example 3: 
//
// 
//Input: nums = [3,2,20,1,1,3], x = 10
//Output: 5
//Explanation: The optimal solution is to remove the last three elements and the
// first two elements (5 operations in total) to reduce x to zero.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// 1 <= nums[i] <= 104 
// 1 <= x <= 109 
// 
// Related Topics Two Pointers Binary Search Greedy Sliding Window 
// 👍 931 👎 19


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        unordered_map<int,int>Map;
        int presum = 0;
        Map[0] = -1;
        for (int i=0; i<n; i++)
        {
            presum += nums[i];
            if (Map.find(presum)==Map.end())
                Map[presum] = i;
        }

        int ret = INT_MAX;
        if (Map.find(x)!=Map.end())
            ret = Map[x]+1;

        int sufsum = 0;
        for (int b = n-1; b>=0; b--)
        {
            sufsum += nums[b];
            int pre = x - sufsum;
            if (Map.find(pre)!=Map.end())
            {
                int a = Map[pre];
                if (a<b)
                {
                    ret = min(ret, a+1 + n-b);
                }
            }
        }

        return ret==INT_MAX ? -1: ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
