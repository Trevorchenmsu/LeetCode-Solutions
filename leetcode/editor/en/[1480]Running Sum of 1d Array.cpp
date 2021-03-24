//Given an array nums. We define a running sum of an array as runningSum[i] = su
//m(nums[0]…nums[i]). 
//
// Return the running sum of nums. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3,4]
//Output: [1,3,6,10]
//Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4]. 
//
// Example 2: 
//
// 
//Input: nums = [1,1,1,1,1]
//Output: [1,2,3,4,5]
//Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+
//1+1+1]. 
//
// Example 3: 
//
// 
//Input: nums = [3,1,2,10,1]
//Output: [3,4,6,16,17]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// -10^6 <= nums[i] <= 10^6 
// Related Topics Array 
// 👍 1114 👎 106


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: brute force
 * time: O(n^2)
 * space: O(1)
 * */
//class Solution {
//public:
//    vector<int> runningSum(vector<int>& nums) {
//        vector<int> res;
//        if (nums.empty()) return res;
//
//        for (int i = 0; i < nums.size(); i++) {
//            int sum = 0;
//            for (int j = 0; j <= i; j++) {
//                sum += nums[j];
//            }
//            res.push_back(sum);
//        }
//
//        return res;
//    }
//};

/*
* Solution 1: brute force
* time: O(n)
* space: O(1)
* */
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res;
        if (nums.empty()) return res;

        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            res.push_back(sum);
        }

        return res;
    }
};

//Input: nums = [3,1,2,10,1]
//Output: [3,4,6,16,17]

//leetcode submit region end(Prohibit modification and deletion)
