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
        int cur_sum = 0, cnt = 1; // 注意cnt从1开始，因为至少一个子集。

        /*
         * （1）首先明确题目要求的是什么：从数组中划分出m个子集，对每个子集求和，然后求出所有子集和中的最大值。
         * 但是，划分成m个子集可以有多种划分方式，我们的目的就是找出某种划分方式，使得上述的最大值最小。
         * 因此在主函数中用二分法定义了上界和下界，而每次考虑的mid，也是我们认为的在某种划分下，
         * 子集和中的最大值，但却是最小最大值的那个，所以在这里的子函数中mid作为子集和的边界。
         * （2）当累积和大于mid/sum时，表示元素加多了，因为mid是边界，子集和不能比它大，否则怎么能认为mid是最大
         * 所以此时我们把cur_sum初始化为当前元素num，相当于认为num前面的元素加了一个子集和，反正小于mid，因此计数器
         * 这里加1。但是如果这些小于mid的子集划分个数比指定的m还多，那就表明这个mid设定得不合理，也是说mid设置过小了，
         * 导致子集划分的数量多了，所以此时需要增大mid，因此在二分法中，就让start=mid往大的方向走，得到更大的mid。
         * 如果整体下来划分顺利的话，表明当前的mid是合理的，那么，我们的目的是求得更小的最大值，所以应该让end=mid往小的方向
         * 走，这样就可以考虑更小的mid。
         * */
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
