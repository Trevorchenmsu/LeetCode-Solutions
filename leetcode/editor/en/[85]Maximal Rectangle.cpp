//Given a rows x cols binary matrix filled with 0's and 1's, find the largest re
//ctangle containing only 1's and return its area. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1",
//"1"],["1","0","0","1","0"]]
//Output: 6
//Explanation: The maximal rectangle is shown in the above picture.
// 
//
// Example 2: 
//
// 
//Input: matrix = []
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: matrix = [["0"]]
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: matrix = [["1"]]
//Output: 1
// 
//
// Example 5: 
//
// 
//Input: matrix = [["0","0"]]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// rows == matrix.length 
// cols == matrix[i].length 
// 0 <= row, cols <= 200 
// matrix[i][j] is '0' or '1'. 
// 
// Related Topics Array Dynamic Programming Stack Matrix Monotonic Stack 
// 👍 5101 👎 93


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dp + monotonic stack
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int rectangleHistogram(vector<int>& heights){
        stack<int> s;
        int res = 0;

        for(int j = 0; j <= heights.size();){
            int curHeight = j == heights.size() ? 0 : heights[j];
            if(!s.empty() && curHeight < heights[s.top()]){
                int height = heights[s.top()]; s.pop();
                int leftBound = s.empty() ? -1 : s.top();
                int width = j - 1 - leftBound;
                if (height == width) {
                    res = max(res, height * width);
                }
            } else{
                s.push(j++);
            }
        }
        return sqrt(res);
    }

    int maximalRectangle(vector<vector<int>>& matrix) {
        // corner case
        if(matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0){
            return 0;
        }

        // initialization
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int> (col + 1));
        int res = 0;

        // traverse the matrix
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if (matrix[i][j] == 1) {
                    dp[i][j] = i == 0 ? 1 : dp[i - 1][j] + 1
                }
                else {
                    dp[i][j] = 0;
                }
            }
            res = max(res, rectangleHistogram(dp[i]));
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
