//Given a pattern and a string s, return true if s matches the pattern. 
//
// A string s matches a pattern if there is some bijective mapping of single cha
//racters to strings such that if each character in pattern is replaced by the str
//ing it maps to, then the resulting string is s. A bijective mapping means that n
//o two characters map to the same string, and no character maps to two different 
//strings. 
//
// 
// Example 1: 
//
// 
//Input: pattern = "abab", s = "redblueredblue"
//Output: true
//Explanation: One possible mapping is as follows:
//'a' -> "red"
//'b' -> "blue" 
//
// Example 2: 
//
// 
//Input: pattern = "aaaa", s = "asdasdasdasd"
//Output: true
//Explanation: One possible mapping is as follows:
//'a' -> "asd"
// 
//
// Example 3: 
//
// 
//Input: pattern = "abab", s = "asdasdasdasd"
//Output: true
//Explanation: One possible mapping is as follows:
//'a' -> "a"
//'b' -> "sdasd"
//Note that 'a' and 'b' cannot both map to "asd" since the mapping is a bijectio
//n.
// 
//
// Example 4: 
//
// 
//Input: pattern = "aabb", s = "xyzabcxzyabc"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= pattern.length, s.length <= 20 
// pattern and s consist of only lower-case English letters. 
// 
// Related Topics Hash Table String Backtracking 
// 👍 599 👎 44


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtrack
 * time: O(s^p)，每次递归有s种匹配串，一共有p次
 * space: O(p)，哈希表和哈希集存储p中字符
 * */
class Solution {
public:
    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> chTostr;
        unordered_set<string> visited;
        return match(pattern, s, chTostr, visited);
    }

    bool match(const string& p, const string& s, unordered_map<char, string>& chTostr, unordered_set<string>& visited) {
        // 当p为空时，s必须为空才能匹配
        if (p.size() == 0) {
            return s.size() == 0;
        }

        // 因为p每次递归都在缩小，所以考虑第一个字符就是在原始p中的下一个新字符
        char ch = p[0];

        // p中该字符在前面已经被匹配过
        auto it = chTostr.find(ch);
        if (it != chTostr.end()) {
            string word_p = chTostr[ch];
            string word_s = s.substr(0, word_p.size());
            if (word_p != word_s) {
                return false;
            }

            return match(p.substr(1), s.substr(word_p.size()), chTostr, visited);
        }

        // p中该字符未被匹配过，所以需要考虑s的所以字符情况进行暴力搜索
        for (int i = 0; i < s.size(); i++) {
            string word = s.substr(0, i + 1);

            // 当前单词前面已经跟其它字符匹配过了，题目中规定不能多匹配，所以skip
            auto it = visited.find(word);
            if (it != visited.end()) {
                continue;
            }

            // 当p与word可以进行匹配，接下来进行回溯考虑所有子情况是否也能够正确匹配
            chTostr[ch] = word;
            visited.insert(word);

            if (match(p.substr(1), s.substr(word.size()), chTostr, visited)){
                return true;
            }

            chTostr.erase(ch);
            visited.erase(word);
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
