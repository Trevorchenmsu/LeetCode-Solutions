//Given two strings s and t of lengths m and n respectively, return the minimum 
//window substring of s such that every character in t (including duplicates) is i
//ncluded in the window. If there is no such substring, return the empty string ""
//. 
//
// The testcases will be generated such that the answer is unique. 
//
// A substring is a contiguous sequence of characters within the string. 
//
// 
// Example 1: 
//
// 
//Input: s = "ADOBECODEBANC", t = "ABC"
//Output: "BANC"
//Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' fr
//om string t.
// 
//
// Example 2: 
//
// 
//Input: s = "a", t = "a"
//Output: "a"
//Explanation: The entire string s is the minimum window.
// 
//
// Example 3: 
//
// 
//Input: s = "a", t = "aa"
//Output: ""
//Explanation: Both 'a's from t must be included in the window.
//Since the largest window of s only has one 'a', return empty string.
// 
//
// 
// Constraints: 
//
// 
// m == s.length 
// n == t.length 
// 1 <= m, n <= 105 
// s and t consist of uppercase and lowercase English letters. 
// 
//
// 
//Follow up: Could you find an algorithm that runs in O(m + n) time? Related Top
//ics Hash Table String Sliding Window 
// 👍 7240 👎 466


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sliding window + hash table
 * time: O(m+n)
 * space: O(n)
 * */
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> char2freq;

        // 用哈希表存储字符在t中的出现频率
        for (auto &ch : t) {
            char2freq[ch]++;
        }

        int left = 0, cnt = 0, len = t.size();
        string res = "";

        for (int right = 0; right < s.size(); right++) {
            // 当右指针经过一个字符时，对它的频率进行减1
            char2freq[s[right]]--;
            // 如果该字符频率自减后大于等于0，表明在t中是有这个字符的，否则会是负数。因此在这里计数器加1。可能存在重复字符，所以不仅仅是等于0
            if (char2freq[s[right]] >= 0) {
                cnt++;
            }

            // 当计数器累计到t的长度时，表明t中所有字符都涉及到了
            while (cnt == len) {
                // 第一次进来时res为空，或者遇到更短的有效字符串时，此时需要更新res
                if (res == "" || right - left + 1 < res.size()) {
                    res = s.substr(left, right -left + 1);
                }

                // 下面的操作主要是滑窗的收缩。因为滑窗收缩左指针要前进，所以左指针当前的字符退出窗口，因此频率自增进行还原
                char2freq[s[left]]++;

                // 当左指针对应字符频率还原后的频率大于0，表明它是t中的某个字符，否则这里要么为0，要么为负数
                // 所以大于0的情况下因为少考虑了一个t中的字符，计数器自减
                if (char2freq[s[left]] > 0){
                    cnt--;
                }

                // 处理完毕后左指针才前进
                left++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
