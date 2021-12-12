//The n-queens puzzle is the problem of placing n queens on an n x n chessboard 
//such that no two queens attack each other. 
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You
// may return the answer in any order. 
//
// Each solution contains a distinct board configuration of the n-queens' placem
//ent, where 'Q' and '.' both indicate a queen and an empty space, respectively. 
//
// 
// Example 1: 
//
// 
//Input: n = 4
//Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
//Explanation: There exist two distinct solutions to the 4-queens puzzle as show
//n above
// 
//
// Example 2: 
//
// 
//Input: n = 1
//Output: [["Q"]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 9 
// 
// Related Topics Array Backtracking 
// 👍 4233 👎 129


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtrack
 * time: O(s*n^2)，s为方案总数，具体大小很难定义，s远小于排序总和n!，如果非要取上限，可认为s=n!
 * space: O(n)，每次存储cols
 * */
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        if (n == 0) {
            return res;
        }

        vector<int> cols;
        search(n, cols, res);

        return res;
    }

    void search(int n, vector<int> &cols, vector<vector<string>> &res) {
        // 因为cols从0开始，每次加入一个元素。这里取它的size，相当于行的递增，即逐行考虑
        int row = cols.size();
        // 当row等于n时，表示所有行已被走完且满足要求，所以添加结果
        if (row == n) {
            vector<string> board = drawBoard(cols); // draw one of the solved board
            res.push_back(board);
        }

        // 拆解递归，具体考虑每一列
        for (int col = 0; col < n; col++) {
            // 检查皇后是否同行/同列/同对角线
            if (!isValid(row, col, cols)) {
                continue;
            }

            // 该列满足要求，使用回溯进行下一层递归
            cols.push_back(col);
            search(n, cols, res);
            cols.pop_back();
        }
    }

    vector<string> drawBoard(vector<int> &cols){
        vector<string> res;
        for (int i = 0; i < cols.size(); i++) {
            string layer = "";
            for (int j = 0; j < cols.size(); j++) {
                layer  += cols[i] == j ? "Q" : ".";
            }
            res.push_back(layer);
        }

        return res;
    }

    bool isValid(int row, int col, vector<int> &cols) {
        for (int r = 0; r < cols.size(); r++) {
            int c = cols[r];
            // 皇后同行/同列
            if (row == r || col == c) {
                return false;
            }
            // 皇后同对角线
            if (row - col == r - c || row + col == r + c) {
                return false;
            }
        }

        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
