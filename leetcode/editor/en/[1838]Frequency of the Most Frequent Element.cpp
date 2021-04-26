//The frequency of an element is the number of times it occurs in an array. 
//
// You are given an integer array nums and an integer k. In one operation, you c
//an choose an index of nums and increment the element at that index by 1. 
//
// Return the maximum possible frequency of an element after performing at most 
//k operations. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,4], k = 5
//Output: 3
//Explanation: Increment the first element three times and the second element tw
//o times to make nums = [4,4,4].
//4 has a frequency of 3. 
//
// Example 2: 
//
// 
//Input: nums = [1,4,8,13], k = 5
//Output: 2
//Explanation: There are multiple optimal solutions:
//- Increment the first element three times to make nums = [4,4,8,13]. 4 has a f
//requency of 2.
//- Increment the second element four times to make nums = [1,8,8,13]. 8 has a f
//requency of 2.
//- Increment the third element five times to make nums = [1,4,13,13]. 13 has a 
//frequency of 2.
// 
//
// Example 3: 
//
// 
//Input: nums = [3,9,6], k = 2
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// 1 <= nums[i] <= 105 
// 1 <= k <= 105 
// 
// Related Topics Greedy 
// 👍 176 👎 5


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1 : presum + binary search
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end()); // O(nlogn)
        int n = nums.size();

        // compute presum
        vector<long> presum(n + 1, 0);
        for (int i = 0; i < n; i++) // O(n)
            presum[i + 1] = presum[i] + nums[i];

        int res = 0;
        for (int i = 0; i < n; i++) { // O(nlogn)
            res = max(res, binarySearch(nums, k, 0, i, presum));
        }

        return res;
    }

private:
    int binarySearch(vector<int> &nums, int k, int left_bound, int right_bound, vector<long> &presum) {
        int start = left_bound, end = right_bound;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (helper(nums, k, mid, right_bound, presum))
                end = mid;
            else
                start = mid;
        }

        if (helper(nums, k, start, right_bound, presum))
            return right_bound - start + 1;

        return right_bound - end + 1;
    }

    bool helper(vector<int> &nums, int k, int start, int end, vector<long> &presum) {
        long sum = presum[end] - presum[start];
        long cnt = (long) nums[end] * (long) (end - start);
        return sum + k >= cnt;
    }
};


/*
 * solution 2 : two pointers
 * time: O(nlogn)
 * space: O(1)
 *
 * */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int left = 0, right = 0, res = 0, n = nums.size();
        long sum = 0;
        sort(nums.begin(), nums.end());

        while (right < n) {
            if (sum > k) {
                sum -= (nums[right] - nums[left]);
                left++;
            }
            else {
                res = max(res, right - left + 1);
                right++;
                if (right < n)
                    sum += (long) (right - left) * (nums[right] - nums[right - 1]);
            }
        }

        return res;
    }

};



/*
 * solution 3 : sliding window, optimal (non-shrinkable window)
 * time: O(nlogn)
 * space: O(1)
 *
 * */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int left = 0, right = 0, n = nums.size();
        sort(nums.begin(), nums.end());
        long sum = k;

        while (right < n) {
            sum += nums[right];
            if ((long) nums[right] * (right - left + 1) > sum)
                sum -= nums[left++];
            right++;
        }

        return right - left;
    }

};


/*
 * solution 4: sliding window, optimal (shrinkable window)
 * time: O(nlogn)
 * space: O(1)
 *
 * */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int left = 0, right = 0, res = 1, n = nums.size();
        sort(nums.begin(), nums.end());
        long sum = k;

        while (right < n) {
            sum += nums[right];
            while ((long) nums[right] * (right - left + 1) > sum)
                sum -= nums[left++];
            res = max(res, right -  left + 1);
            right++;
        }

        return res;
    }

};

//leetcode submit region end(Prohibit modification and deletion)
