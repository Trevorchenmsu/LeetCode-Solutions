//The string "PAYPALISHIRING" is written in a zigzag pattern on a given number o
//f rows like this: (you may want to display this pattern in a fixed font for bett
//er legibility) 
//
// 
//P   A   H   N
//A P L S I I G
//Y   I   R
// 
//
// And then read line by line: "PAHNAPLSIIGYIR" 
//
// Write the code that will take a string and make this conversion given a numbe
//r of rows: 
//
// 
//string convert(string s, int numRows);
// 
//
// 
// Example 1: 
//
// 
//Input: s = "PAYPALISHIRING", numRows = 3
//Output: "PAHNAPLSIIGYIR"
// 
//
// Example 2: 
//
// 
//Input: s = "PAYPALISHIRING", numRows = 4
//Output: "PINALSIGYAHRPI"
//Explanation:
//P     I    N
//A   L S  I G
//Y A   H R
//P     I
// 
//
// Example 3: 
//
// 
//Input: s = "A", numRows = 1
//Output: "A"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// s consists of English letters (lower-case and upper-case), ',' and '.'. 
// 1 <= numRows <= 1000 
// 
// Related Topics String 
// 👍 3684 👎 8475


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers and implementation, python的解法更高效
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> row_string(numRows, "");
        int n = s.size(), i = 0;
s
        while (i < n)
        {
            for (int j = 0; j < numRows && i < n; ++j)
                row_string[j].push_back(s[i++]);

            for (int j = numRows - 2; j >= 1 && i < n; --j)
                row_string[j].push_back(s[i++]);
        }

        string zigzag = "";

        for (auto rs : row_string)
            zigzag += rs;

        return zigzag;
    }
};

class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1 or numRows >= len(s):
            return s

        row_string = [''] * numRows
        row, step = 0, 1

        for c in s:
            row_string[row] += c

            # 用step的正负来控制从上到下以及从下到上的遍历方向转换
            if row == 0:
            step = 1
            elif row == numRows -1:
            step = -1

            row += step

        return ''.join(row_string)
//leetcode submit region end(Prohibit modification and deletion)
