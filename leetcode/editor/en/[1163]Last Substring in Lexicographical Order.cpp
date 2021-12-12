//Given a string s, return the last substring of s in lexicographical order. 
//
// 
// Example 1: 
//
// 
//Input: s = "abab"
//Output: "bab"
//Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. 
//The lexicographically maximum substring is "bab".
// 
//
// Example 2: 
//
// 
//Input: s = "leetcode"
//Output: "tcode"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 4 * 105 
// s contains only lowercase English letters. 
// 
// Related Topics Two Pointers String 
// 👍 353 👎 379


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string lastSubstring(string s) {
        int left = 0, right = 1, k = 0, n = s.size();
        while (right + k < n) {
            if (s[left + k] == s[right + k]) {
                k++;
            }
            else if (s[left] < s[right + k]) {
                left = right + k;
                right = right + k + 1;
                k = 0;
            }
            else if (s[left + k] < s[right + k]) {
                left = right;
                right++;
                k = 0;
            }
            else {
                right++;
                k = 0;
            }
        }

        return s.substr(left);
    }
};

/*
 * solution 2: two pointers
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    string lastSubstring(string s) {
        int ind = 0, right = 1;;

        while (right < s.size()) {
            int left = ind;

            while (s[left] == s[right]) {
                left++,right++;
            }

            if (s[right] > s[ind]) {
                ind = right++;
            }
            else if (s[left] < s[right]) {
                ind = right + ind - left;
                right = ind + 1;
            }
            else  {
                right++;
            }
        }
        return s.substr(ind);
    }
};






//leetcode submit region end(Prohibit modification and deletion)
