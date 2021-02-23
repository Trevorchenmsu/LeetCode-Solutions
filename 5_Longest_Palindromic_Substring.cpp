/*
solution 1: central line scan
time: O(n^2)
space: O(1)
*/
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";
        if (s.empty()) return res;
        
        for (int i = 0; i < s.length(); i++) {
            string oddPalindrome = getPalindromeFrom(s, i, i);
            if (res.length() < oddPalindrome.length())
                res = oddPalindrome;
            
            string evenPalindrome = getPalindromeFrom(s, i, i + 1);
            if (res.length() < evenPalindrome.length())
                res = evenPalindrome;
        }
        
        return res;
    }

private:
    string getPalindromeFrom(string &s, int left, int right) {
        while (left >= 0 && right < s.length()) {
            if (s[left] != s[right])
                break;
            left--;
            right++;
        }
        return s.substr(left + 1, right - left - 1);
    }
};

/*
solution 2: dp
time: O(n^2)
space: O(n^2)
*/
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";
        if (s.empty()) return res;
        
        int n = s.length();
        int isPalindrome[n][n];
        memset(isPalindrome, 0, sizeof(isPalindrome));
        
        // initialization
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = 1;  // single character
            if (i > 0)
                isPalindrome[i][i - 1] = true; // empty string
        }
        
        int start = 0, longest = 1;
        for (int length = 2; length <= n; length++) { // start from two character
            for (int i = 0; i + length <= n; i++) {
                int j = i - 1 + length;
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && s[i] == s[j];
                if (isPalindrome[i][j] && longest < length) {
                    start = i;
                    longest = length;
                }
            }
        }
        
        return s.substr(start, longest);
    }
};
