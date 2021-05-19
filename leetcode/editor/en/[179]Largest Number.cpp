//Given a list of non-negative integers nums, arrange them such that they form t
//he largest number. 
//
// Note: The result may be very large, so you need to return a string instead of
// an integer. 
//
// 
// Example 1: 
//
// 
//Input: nums = [10,2]
//Output: "210"
// 
//
// Example 2: 
//
// 
//Input: nums = [3,30,34,5,9]
//Output: "9534330"
// 
//
// Example 3: 
//
// 
//Input: nums = [1]
//Output: "1"
// 
//
// Example 4: 
//
// 
//Input: nums = [10]
//Output: "10"
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 100 
// 0 <= nums[i] <= 109 
// 
// Related Topics Sort 
// 👍 3059 👎 319


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sort
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
    static bool cmp(string &s1, string &s2) {
        return (s1 + s2) > (s2 + s1);
    }
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        for (auto &num : nums)
            strs.push_back(to_string(num));

        sort(strs.begin(), strs.end(), cmp);

        string res;
        for (auto &str : strs)
            res += str;

        int i = 0;
        while (res[i] == '0') i++;

        if (i == res.size()) return "0";
        else return res.substr(i);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
