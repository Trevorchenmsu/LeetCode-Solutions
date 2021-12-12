//Given an array of integers nums and an integer k, return the total number of c
//ontinuous subarrays whose sum equals to k. 
//
// 
// Example 1: 
// Input: nums = [1,1,1], k = 2
//Output: 2
// Example 2: 
// Input: nums = [1,2,3], k = 3
//Output: 2
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 2 * 104 
// -1000 <= nums[i] <= 1000 
// -107 <= k <= 107 
// 
// Related Topics Array Hash Table Prefix Sum 
// 👍 8431 👎 286


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force, prefix sum, TLE
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, n = nums.size();
        vector<int> sums (n, 0);
        sums[0] = nums[0];
        for (int i = 1; i < n; i++) {
            sums[i] = sums[i - 1] + nums[i];
        }

        for (int i = 0; i < n; i++) {
            if (sums[i] == k) {
                res++;
            }

            for (int j = i - 1; j >= 0; j--) {
                if (i > 0 && sums[i] - sums[j] == k) {
                    res++;
                }
            }
        }

        return res;

    }
};


/*
 * solution 2: hash table + prefix sum
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, sum = 0, n = nums.size();
        // 初始化(0,1)是必要的，否则找到第一个sum-k的数时，频率不会是1开始
        unordered_map<int, int> sum2freq{{0, 1}};

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            // 如果还未找到sum-k=0的情况，即子数组和不为K时，因为哈希表初始化都为0，所以res一直加的都是0
            // 直到找到子数组和等于k的情况，就得到了第一个sum-k=0。因为我们初始化0对应的频率为1，所以这里res会加1
            // 然后更新哈希表的内容，表示已经出现过的sum的频率加1.
            res += sum2freq[sum - k];
            sum2freq[sum]++;
        }

        return res;
    }
};


/*
 * solution 3: hash table + prefix sum， optimal
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        int sum = 0;
        int res = 0;
        unordered_map<int,int> sum2cnt;

        /* 哈希表：每个前缀和的出现频率，由于遍历数组的时候逐渐扫过去，所以每个前缀和的频率只会是一次
         * 为什么可以用哈希表查找？首先我们看查找的是sum-k，假设a+k=sum，相当于数组前半部之和为a，后面某部分之和为k
         * 也就是我们想从数组中间算其他子数组的情况。在前期，如果前缀和得到了等于k的情况，那么就直接res++。随后前缀和会一直变大
         * 当前缀和变大到某种程度时，sum-k在哈希表中有存在，那么就证明有一段的和为a，一段的和为k，所以这时候我们找到的是后面那一段
         * 和为k的子数组。
         * */

        for(int &num : nums){
            sum += num;

            if(sum == k) {
                res++;
            }

            auto iter = sum2cnt.find(sum - k);
            if(iter != sum2cnt.end()) {
                res += sum2cnt.at(sum - k);
            }

            sum2cnt[sum]++;
        }

        return res;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
