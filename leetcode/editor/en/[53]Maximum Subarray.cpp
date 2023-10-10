//Given an integer array nums, find the contiguous subarray (containing at least
// one number) which has the largest sum and return its sum. 
//
// A subarray is a contiguous part of an array. 
//
// 
// Example 1: 
//
// 
//Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
//Output: 6
//Explanation: [4,-1,2,1] has the largest sum = 6.
// 
//
// Example 2: 
//
// 
//Input: nums = [1]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: nums = [5,4,-1,7,8]
//Output: 23
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 3 * 104 
// -105 <= nums[i] <= 105 
// 
//
// 
// Follow up: If you have figured out the O(n) solution, try coding another solu
//tion using the divide and conquer approach, which is more subtle. 
// Related Topics Array Divide and Conquer Dynamic Programming 
// 👍 13610 👎 645


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: Kadane algorithm
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN, curSum = 0;
        for (const auto &num : nums) {
            curSum = max(curSum + num, num);
            res = max(res, curSum);
        }

        return res;
    }
};

/*
 * solution 2: dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int res = dp[0];
        for(int i = 1; i < nums.size(); i++){
            /*  这里从dp[i-1]+nums[i]和nums[i]选一个较大的原因:dp[i-1]为前面累积和，可为正负零。如果它是正或者零，加上nums[i]的结果
             * 肯定也还是dp[i-1]+nums[i]，也就是说dp[i-1]对于求子数组和是有正面贡献的。当dp[i-1]为负时则是负面贡献，我们想要更大的子数组
             * 和，肯定不要前面给的负面贡献，因此从当前这个位置开始，摈弃之前的和，所以选择更大的nums[i]
             * */
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
//            dp[i] = nums[i] + max(0, dp[i - 1]); 第二种表达
            res = max(res, dp[i]);
        }
        return res;
    }
};


/*
 * solution 3: prefix sum
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) {
            return 0;
        }

        int res = INT_MIN, minPrefixSum = 0, curSum = 0;

        for (const auto& num : nums) {
            curSum += num;
            res = max(res, curSum - minPrefixSum);
            minPrefixSum = min(curSum, minPrefixSum);
        }

        return res;
    }
};


/*
 * solution 4: divide and conquer
 * time:
 * space:
 * */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return maxSubArray(nums, 0, nums.size() - 1);
    }
private:
    /*
     * 既然是分治的思想，且我们的目的是求子数组最大和，那肯定是要分开两段来求子数组最大和，左段子数组最大和以及右段子数组最大和。
     * 注意下面分治与普通分治的区别，下面的左右段区分区间为(left, mid-1)和(mid+1,right),左段不包括mid。这样的目的是为了
     * 跟下面的nums[mid]加起来，这样才可以形成一个连续子数组。
     * */
    int maxSubArray(vector<int>& nums, int left, int right) {
        if (left > right) {
            return INT_MIN;
        }

        int mid = left + (right - left) / 2,  l_max = 0, r_max = 0;
        int left_max = maxSubArray(nums, left, mid - 1);
        int right_max = maxSubArray(nums, mid + 1, right);

        /* 为什么左右段可以这样直接累加？因为不管后面的值是负还是正，我们总是取较大值，如果后面的一直都是负的，
            虽然累积和一直在减小，但是因为我们采用max，所以对l_max没影响，实际上就相当于我们忽略了后面的负
            的部分。如果后面的一直的都是正的，则累积和一直在增大，实际上就相当于我们一直在扩大有效子数组的范围。
            类似中心扩散法的思路。
         */
        for (int i = mid - 1, sum = 0; i >= left; i--) {
            sum += nums[i];
            l_max = max(sum, l_max);
        }

        for (int i = mid + 1, sum = 0; i <= right; i++) {
            sum += nums[i];
            r_max = max(sum, r_max);
        }

        /*
         * 这里最终的结果就是三段的大比拼：（1）left_max；（2）right_max； （3）l_max + r_max + nums[mid]
         * 以mid为中点，（3）得到的就是从left到right这个区间的累计和。left_max则为left到mid-1的累计和，right_max
         * 则为mid+1到right的累计和。因为递归的作用，这个mid是一直在每个位置变化的，所以基本上就可以求出整个数组的最大累积
         * 和分布。
         * */
        return max(max(left_max, right_max), l_max + r_max + nums[mid]);
    }
};

//leetcode submit region end(Prohibit modification and deletion)
