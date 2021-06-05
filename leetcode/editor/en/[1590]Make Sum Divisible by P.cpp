//Given an array of positive integers nums, remove the smallest subarray (possib
//ly empty) such that the sum of the remaining elements is divisible by p. It is n
//ot allowed to remove the whole array. 
//
// Return the length of the smallest subarray that you need to remove, or -1 if 
//it's impossible. 
//
// A subarray is defined as a contiguous block of elements in the array. 
//
// 
// Example 1: 
//
// 
//Input: nums = [3,1,4,2], p = 6
//Output: 1
//Explanation: The sum of the elements in nums is 10, which is not divisible by 
//6. We can remove the subarray [4], and the sum of the remaining elements is 6, w
//hich is divisible by 6.
// 
//
// Example 2: 
//
// 
//Input: nums = [6,3,5,2], p = 9
//Output: 2
//Explanation: We cannot remove a single element to get a sum divisible by 9. Th
//e best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
// 
//
// Example 3: 
//
// 
//Input: nums = [1,2,3], p = 3
//Output: 0
//Explanation: Here the sum is 6. which is already divisible by 3. Thus we do no
//t need to remove anything.
// 
//
// Example 4: 
//
// 
//Input: nums = [1,2,3], p = 7
//Output: -1
//Explanation: There is no way to remove a subarray in order to get a sum divisi
//ble by 7.
// 
//
// Example 5: 
//
// 
//Input: nums = [1000000000,1000000000,1000000000], p = 3
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// 1 <= nums[i] <= 109 
// 1 <= p <= 109 
// 
// Related Topics Array Hash Table Math Binary Search 
// 👍 552 👎 26


//leetcode submit region begin(Prohibit modification and deletion)
typedef long long ll;
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        unordered_map<int,int>Map;
        Map[0] = -1;

        ll sum = 0;
        for (auto a: nums)
            sum = (sum+a)%p;
        ll r0 = sum % p;
        if (r0==0) return 0;

        ll presum = 0;
        int ret = INT_MAX;

        for (int i=0; i<n; i++)
        {
            presum += nums[i];
            presum %= p;
            ll r = presum % p;
            ll diff = (r+p-r0) % p;

            if (Map.find(diff)!=Map.end())
                ret = min(ret, i-Map[diff]);
            Map[r] = i;
        }

        if (ret>=n)
            return -1;
        else
            return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
