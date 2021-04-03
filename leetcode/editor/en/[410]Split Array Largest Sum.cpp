//Given an array nums which consists of non-negative integers and an integer m, 
//you can split the array into m non-empty continuous subarrays. 
//
// Write an algorithm to minimize the largest sum among these m subarrays. 
//
// 
// Example 1: 
//
// 
//Input: nums = [7,2,5,10,8], m = 2
//Output: 18
//Explanation:
//There are four ways to split nums into two subarrays.
//The best way is to split it into [7,2,5] and [10,8],
//where the largest sum among the two subarrays is only 18.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,4,5], m = 2
//Output: 9
// 
//
// Example 3: 
//
// 
//Input: nums = [1,4,4], m = 3
//Output: 4
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// 0 <= nums[i] <= 106 
// 1 <= m <= min(50, nums.length) 
// 
// Related Topics Binary Search Dynamic Programming 
// 👍 2509 👎 92


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search
 * time: O(nlog(sum-maxN))
 * space: O(1)
 * */
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        // compute lower bound and upper bound
        long start = 0, end = 0;
        for (int i = 0; i < nums.size(); i++) { // O(n)
            start = max(start, (long) nums[i]);
            end += nums[i];
        }

        while (start < end) { // O(nlog(sum-maxN))
            long mid = start + (end - start) / 2;
            if (canSplit(nums, m, mid))
                end = mid;
            else
                start = mid + 1;
        }

        return end;
    }

private:
    bool canSplit(vector<int> &nums, int m, long sum) {
        int cur_sum = 0, cnt = 1;

        for (auto &num : nums) {
            cur_sum += num;
            if (cur_sum > sum) {
                cur_sum = num;
                cnt++;
                if (cnt > m) return false;
            }
        }

        return true;
    }
};



/*
 * solution 2 binary search
 * time: O(nlog(sum-maxN))
 * space: O(1)
 * */
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        // compute lower bound and upper bound
        long start = 0, end = 0;
        for (int i = 0; i < nums.size(); i++) { // O(n)
            start = max(start, (long) nums[i]);
            end += nums[i];
        }

        while (start + 1 < end) { // O(nlog(sum-maxN))
            long mid = start + (end - start) / 2;
            if (canSplit(nums, m, mid))
                end = mid;
            else
                start = mid;
        }

        if (canSplit(nums, m, start)) return start;

        return end;
    }

private:
    bool canSplit(vector<int> &nums, int m, long sum) {
        int cur_sum = 0, cnt = 1;

        for (auto &num : nums) {
            cur_sum += num;
            if (cur_sum > sum) {
                cur_sum = num;
                cnt++;
                if (cnt > m) return false;
            }
        }

        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
