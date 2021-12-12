//You are given a string s, a split is called good if you can split s into 2 non
//-empty strings p and q where its concatenation is equal to s and the number of d
//istinct letters in p and q are the same. 
//
// Return the number of good splits you can make in s. 
//
// 
// Example 1: 
//
// 
//Input: s = "aacaba"
//Output: 2
//Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
//("a", "acaba") Left string and right string contains 1 and 3 different letters
// respectively.
//("aa", "caba") Left string and right string contains 1 and 3 different letters
// respectively.
//("aac", "aba") Left string and right string contains 2 and 2 different letters
// respectively (good split).
//("aaca", "ba") Left string and right string contains 2 and 2 different letters
// respectively (good split).
//("aacab", "a") Left string and right string contains 3 and 1 different letters
// respectively.
// 
//
// Example 2: 
//
// 
//Input: s = "abcd"
//Output: 1
//Explanation: Split the string as follows ("ab", "cd").
// 
//
// Example 3: 
//
// 
//Input: s = "aaaaa"
//Output: 4
//Explanation: All possible splits are good. 
//
// Example 4: 
//
// 
//Input: s = "acbadbaada"
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// s contains only lowercase English letters. 
// 1 <= s.length <= 10^5 
// Related Topics String Dynamic Programming Bit Manipulation 
// 👍 936 👎 25


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table + dp思想
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    int numSplits(string s) {
        if (s.empty() || s.size() <= 1) {
            return 0;
        }

        // 采用两个哈希表，左边记录不同字符的频率，右边记录不同单词的频率，只要两个哈希表的size相等，就res+1
        unordered_map<char, int> left, right;
        for (const auto& ch : s) {
            right[ch]++;
        }

        int n = s.size(), res = 0;

        for (int i = 1; i <= n; i++) {
            left[s[i - 1]]++;

            if (--right[s[i - 1]] == 0) {
                right.erase(s[i - 1]);
            }

            if (left.size() == right.size()) {
                res++;
            }
        }

        return res;
    }
};


//leetcode submit region end(Prohibit modification and deletion)
