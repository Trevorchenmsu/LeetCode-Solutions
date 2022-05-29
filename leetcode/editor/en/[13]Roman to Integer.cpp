//Roman numerals are represented by seven different symbols: I, V, X, L, C, D an
//d M. 
//
// 
//Symbol       Value
//I             1
//V             5
//X             10
//L             50
//C             100
//D             500
//M             1000 
//
// For example, 2 is written as II in Roman numeral, just two one's added togeth
//er. 12 is written as XII, which is simply X + II. The number 27 is written as XX
//VII, which is XX + V + II. 
//
// Roman numerals are usually written largest to smallest from left to right. Ho
//wever, the numeral for four is not IIII. Instead, the number four is written as 
//IV. Because the one is before the five we subtract it making four. The same prin
//ciple applies to the number nine, which is written as IX. There are six instance
//s where subtraction is used: 
//
// 
// I can be placed before V (5) and X (10) to make 4 and 9. 
// X can be placed before L (50) and C (100) to make 40 and 90. 
// C can be placed before D (500) and M (1000) to make 400 and 900. 
// 
//
// Given a roman numeral, convert it to an integer. 
//
// 
// Example 1: 
//
// 
//Input: s = "III"
//Output: 3
// 
//
// Example 2: 
//
// 
//Input: s = "IV"
//Output: 4
// 
//
// Example 3: 
//
// 
//Input: s = "IX"
//Output: 9
// 
//
// Example 4: 
//
// 
//Input: s = "LVIII"
//Output: 58
//Explanation: L = 50, V= 5, III = 3.
// 
//
// Example 5: 
//
// 
//Input: s = "MCMXCIV"
//Output: 1994
//Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 15 
// s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M'). 
// It is guaranteed that s is a valid roman numeral in the range [1, 3999]. 
// 
// Related Topics Hash Table Math String 
// 👍 1873 👎 143


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> roman_to_int = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};


        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i + 1 < n && roman_to_int[s[i]] < roman_to_int[s[i + 1]])
            {
                res += roman_to_int[s[i + 1]] - roman_to_int[s[i]];
                ++i;
            }
            else
            {
                res += roman_to_int[s[i]];
            }
        }

        return res;
    }
};

class Solution:
    def romanToInt(self, s: str) -> int:
        rtoi = {'I':1, 'V':5, 'X':10, 'L':50, 'C':100, 'D':500, 'M':1000}
        n, res, i = len(s), 0, 0

        while i < n:
            if i + 1 < n and rtoi[s[i]] < rtoi[s[i+1]]:
                res += (rtoi[s[i+1]] - rtoi[s[i]])
                i += 1
            else:
             res += rtoi[s[i]]
            i += 1

        return res
//leetcode submit region end(Prohibit modification and deletion)
