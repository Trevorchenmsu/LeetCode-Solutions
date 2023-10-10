//Given a string s, determine if it is a palindrome, considering only alphanumer
//ic characters and ignoring cases. 
//
// 
// Example 1: 
//
// 
//Input: s = "A man, a plan, a canal: Panama"
//Output: true
//Explanation: "amanaplanacanalpanama" is a palindrome.
// 
//
// Example 2: 
//
// 
//Input: s = "race a car"
//Output: false
//Explanation: "raceacar" is not a palindrome.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 2 * 105 
// s consists only of printable ASCII characters. 
// 
// Related Topics Two Pointers String 
// 👍 1922 👎 3773

//Input: s = "A man, a plan, a canal: Panama"
//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !isValid(s[left])) left++;
            while (left < right && !isValid(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            left++, right--;
        }
        return true;
    }

private:
    bool isValid(char ch) {
        return isdigit(ch) || isalpha(ch);
    }
};

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty())
            return true;

        // 1. upper->lower; 2. only character; 3. even/odd
        int left = 0, right = s.length() - 1;
        while (left <= right) {
            if (!isalpha(s[left]) && !isdigit(s[left])) {
                left++;
                continue;
            }

            if (!isalpha(s[right]) && !isdigit(s[right])) {
                right--;
                continue;
            }

            if (tolower(s[left]) != tolower(s[right]))
                return false;

            left++;
            right--;
        }

        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
