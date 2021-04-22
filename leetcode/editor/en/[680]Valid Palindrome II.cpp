//
//Given a non-empty string s, you may delete at most one character. Judge whethe
//r you can make it a palindrome.
// 
//
// Example 1: 
// 
//Input: "aba"
//Output: True
// 
// 
//
// Example 2: 
// 
//Input: "abca"
//Output: True
//Explanation: You could delete the character 'c'.
// 
// 
//
// Note: 
// 
// The string will only contain lowercase characters a-z.
//The maximum length of the string is 50000. 
// 
// Related Topics String 
// 👍 2525 👎 161


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: (n)
 * space:(1)
 *
 * */
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        pair<int, int> diff = findDiff(s, left, right);
        if (diff.first >= diff.second)
            return true;

        return isPalindrome(s, diff.first + 1, diff.second) ||
               isPalindrome(s, diff.first, diff.second - 1);
    }

private:
    pair<int, int> findDiff(string &s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right])
                break;
            left++, right--;
        }

        return make_pair(left, right);
    }

    bool isPalindrome(string &s, int left, int right) {
        pair<int, int>  diff = findDiff(s, left, right);
        return diff.first >= diff.second;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
