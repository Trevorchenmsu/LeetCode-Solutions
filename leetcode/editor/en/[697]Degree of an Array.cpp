//Given a non-empty array of non-negative integers nums, the degree of this arra
//y is defined as the maximum frequency of any one of its elements. 
//
// Your task is to find the smallest possible length of a (contiguous) subarray 
//of nums, that has the same degree as nums. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,2,3,1]
//Output: 2
//Explanation: 
//The input array has a degree of 2 because both elements 1 and 2 appear twice.
//Of the subarrays that have the same degree:
//[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
//The shortest length is 2. So return 2.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,2,3,1,4,2]
//Output: 6
//Explanation: 
//The degree is 3 because the element 2 is repeated 3 times.
//So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.
// 
//
// 
// Constraints: 
//
// 
// nums.length will be between 1 and 50,000. 
// nums[i] will be an integer between 0 and 49,999. 
// 
// Related Topics Array Hash Table 
// 👍 1494 👎 1034


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sliding window + hash table
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> cnts;

        for (auto &num : nums) {
            cnts[num]++;
        }

        int degree = 0;
        for (auto &[num, cnt] : cnts) {
            degree = max(degree, cnt);
        }

        int left = 0, deg = 0, res = INT_MAX;
        unordered_map<int, int> counts;
        for (int right = 0; right < nums.size(); right++) {
            counts[nums[right]]++;
            deg = max(deg, counts[nums[right]]);
            while (deg == degree) {
                res = min(res, right - left + 1);
                counts[nums[left]]--;
                deg = max(counts[nums[right]], counts[nums[left]]);
                left++;
            }
        }

        return res;
    }
};

/*
 * solution 2: sliding window + vector
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) {
            return 0;
        }

        int degree = 0;
        vector<int> cnts(50000, 0);
        for (const auto& num : nums) {
            cnts[num]++;
            degree = max(degree, cnts[num]);
        }

        int left = 0, deg = 0, res = INT_MAX;
        vector<int> freq(50000, 0);
        for (int right = 0; right < nums.size(); right++) {
            freq[nums[right]]++;
            deg = max(deg, freq[nums[right]]);
            while (deg == degree) {
                res = min(res, right - left + 1);
                freq[nums[left]]--;
                deg = max(freq[nums[right]], freq[nums[left]]);
                left++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
