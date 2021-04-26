//Given a string s, find the length of the longest substring without repeating c
//haracters. 
//
// 
// Example 1: 
//
// 
//Input: s = "abcabcbb"
//Output: 3
//Explanation: The answer is "abc", with the length of 3.
// 
//
// Example 2: 
//
// 
//Input: s = "bbbbb"
//Output: 1
//Explanation: The answer is "b", with the length of 1.
// 
//
// Example 3: 
//
// 
//Input: s = "pwwkew"
//Output: 3
//Explanation: The answer is "wke", with the length of 3.
//Notice that the answer must be a substring, "pwke" is a subsequence and not a 
//substring.
// 
//
// Example 4: 
//
// 
//Input: s = ""
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 0 <= s.length <= 5 * 104 
// s consists of English letters, digits, symbols and spaces. 
// 
// Related Topics Hash Table Two Pointers String Sliding Window 
// 👍 14057 👎 728


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sliding window, shrinkable
 * time: O(n)
 * space: O(L), L is the maximum length fo substring with unique characters
 * */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0, res = 0, n = s.size();
        unordered_map<char, int> buckets;

        while (right < n) {
            buckets[s[right]]++;

            while (buckets[s[right]] > 1)
                buckets[s[left++]]--;

            res = max(res, right - left + 1);
            right++;
        }

        return res;
    }
};

/*
 * solution 2: sliding window, non-shrinkable
 * time: O(n)
 * space: O(L), L is the maximum length fo substring with unique characters
 * */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0, n = s.size(), dup = 0;
        unordered_map<char, int> buckets;

        while (right < n) {
            dup += ++buckets[s[right]] == 2;

            if (dup)
                dup -= --buckets[s[left++]] == 1;

            right++;
        }

        return right - left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
