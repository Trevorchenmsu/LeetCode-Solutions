//Given an array of n integers nums and an integer target, find the number of in
//dex triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] 
//+ nums[j] + nums[k] < target. 
// 
// Example 1: 
//
// 
//Input: nums = [-2,0,1,3], target = 2
//Output: 2
//Explanation: Because there are two triplets which sums are less than 2:
//[-2,0,1]
//[-2,0,3]
// 
//
// Example 2: 
//
// 
//Input: nums = [], target = 0
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: nums = [0], target = 0
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// n == nums.length 
// 0 <= n <= 3500 
// -100 <= nums[i] <= 100 
// -100 <= target <= 100 
// 
// Related Topics Array Two Pointers Binary Search Sorting 
// 👍 1132 👎 116


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.size() < 3)
        {
            return 0;
        }

        int res = 0;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            int left = i + 1, right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < target)
                {
                    /*
                    卡点在这一步，例如[1,2,3,4,5,6,7],target=10。当num[i]=1,num[l]=2,num[r]=6时，
                    我的思维认为在l和r区间时，r固定一个值，然后l一直前进获得pair。r--再固定一个值，然后l
                    再前进。但是这个过程中，l前进，r后退会有重复情况，例如l从2走到4时，然后r从6退到4时，这时候
                    考虑固定r，然后l再从头走的话，其实在前面已经考虑过了。所以在l的位置时，用r-l，就表示l右边所有
                    有效的元素个数，相当于i+l+（r-l)个右边点，对于当前i和l。
                    另外，本题允许重复答案，所以不需要去重。
                    */
                    res += right - left;
                    left++;
                }
                else
                {
                    right--;
                }

            }
        }

        return res;
    }
};

/*
 * solution 2: hash table
 * time: O(n^2)
 * space: O(n)
 * */

/*
 * （1）先用哈希表把每个数字的出现频率记录下来。（2）用两个for循环遍历考虑两个数n1和n2，n3就是target减去他们俩。如果哈希表中不存在这个数，就继续循环。
 * （3）如果哈希表存在这个数，就得分情况讨论：当三个数都相等时，要算答案总数，相当于从该数字的总频率中任意选三个，按照组合公式就是C(n,3)，n就是该数的频率数；
 * 如果n1和n2相等，但是不等于n3，相当于从n1数的频率中任意选两个，按照组合公式就是C(n,2)，然后再乘以n3的频率；因为我们没有排序，所以需要满足n1<n2<n3的情况才有效，
 * 在这种情况下，就是直接三个数的频率相乘即可。
 *
 * */
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        long res = 0;
        int MOD = 1e9 + 7;
        unordered_map<int, long> num_cnt;

        for (auto &num : arr) num_cnt[num]++;
        for (auto &nc1 : num_cnt)
        {
            for (auto &nc2 : num_cnt)
            {
                int num1 = nc1.first, num2 = nc2.first, num3 = target - num1 - num2;
                auto it = num_cnt.find(num3);
                if (it == num_cnt.end()) continue;
                if (num1 == num2 && num2 == num3)
                {
                    res += nc1.second * (nc1.second - 1) * (nc1.second - 2) / 6; //组合公式：C(n, 3)
                }
                else if (num1 == num2 && num2 != num3)
                {
                    res += nc1.second * (nc1.second - 1) / 2 * num_cnt[num3];
                }
                else if (num1 < num2 && num2 < num3)
                {
                    res += nc1.second * nc2.second * num_cnt[num3];
                }
            }
        }
        return int (res % MOD);
    }
};

/*
 * solution 3: hash table
 * time: O(n^2)
 * space: O(n)
 * */
/*
 * 主要思路：用哈希表记录两数之和的频率。当遍历数组的某个数arr[i]时，如果能在哈希表中找到target-arr[i]，则表明这是一个有效组合，因此结果加一；
 * 因为遍历到了i这个位置，相当于遇到了一个新数，所以要把这个新数跟前面的旧数一一组合成新的和，然后再增加该和的频率。
 * */
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        long res = 0;
        int MOD = 1e9 + 7;
        unordered_map<int, int> sum_cnt;
        for (int i = 0; i < arr.size(); ++i)
        {
            res = (res + sum_cnt[target - arr[i]]) % MOD;
            for (int j = 0; j < i; ++j)
            {
                sum_cnt[arr[i] + arr[j]]++;
            }
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
