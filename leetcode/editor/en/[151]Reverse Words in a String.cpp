//Given an input string s, reverse the order of the words. 
//
// A word is defined as a sequence of non-space characters. The words in s will 
//be separated by at least one space. 
//
// Return a string of the words in reverse order concatenated by a single space.
// 
//
// Note that s may contain leading or trailing spaces or multiple spaces between
// two words. The returned string should only have a single space separating the w
//ords. Do not include any extra spaces. 
//
// 
// Example 1: 
//
// 
//Input: s = "the sky is blue"
//Output: "blue is sky the"
// 
//
// Example 2: 
//
// 
//Input: s = "  hello world  "
//Output: "world hello"
//Explanation: Your reversed string should not contain leading or trailing space
//s.
// 
//
// Example 3: 
//
// 
//Input: s = "a good   example"
//Output: "example good a"
//Explanation: You need to reduce multiple spaces between two words to a single 
//space in the reversed string.
// 
//
// Example 4: 
//
// 
//Input: s = "  Bob    Loves  Alice   "
//Output: "Alice Loves Bob"
// 
//
// Example 5: 
//
// 
//Input: s = "Alice does not even like bob"
//Output: "bob like even not does Alice"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 104 
// s contains English letters (upper-case and lower-case), digits, and spaces ' 
//'. 
// There is at least one word in s. 
// 
//
// 
// Follow-up: If the string data type is mutable in your language, can you solve
// it in-place with O(1) extra space? 
// Related Topics Two Pointers String 
// 👍 2151 👎 3475


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string reverseWords(string s) {
        string res = "";
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);

        int j = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ' ') {
                continue;
            }

            j = i;
            while (j >= 0 && s[j] != ' ') {
                j--;
            }

            if (j == -1) {
                res += s.substr(j + 1, i - j);
            }
            else {
                res += s.substr(j + 1, i - j) + " ";
            }

            i = j;
        }

        return res;
    }
};

/*
 * solution 2: two pointers， follow up
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int n = s.size(), idx = 0;

        for (int start = 0; start < n; start++) {
            if (s[start] == ' ') {
                continue;
            }

            if (idx != 0) {
                s[idx++] = ' ';
            }

            int end = start;
            while (end < n && s[end] != ' ') {
                s[idx++] = s[end++];
            }

            reverse(s.begin() + idx - (end - start), s.begin() + idx);

            start = end;
        }

        s.erase(s.begin() + idx, s.end());
        return s;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
