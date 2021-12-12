//Given an m x n grid of characters board and a string word, return true if word
// exists in the grid. 
//
// The word can be constructed from letters of sequentially adjacent cells, wher
//e adjacent cells are horizontally or vertically neighboring. The same letter cel
//l may not be used more than once. 
//
// 
// Example 1: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCCED"
//Output: true
// 
//
// Example 2: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "SEE"
//Output: true
// 
//
// Example 3: 
//
// 
//Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCB"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// m == board.length 
// n = board[i].length 
// 1 <= m, n <= 6 
// 1 <= word.length <= 15 
// board and word consists of only lowercase and uppercase English letters. 
// 
//
// 
// Follow up: Could you use search pruning to make your solution faster with a l
//arger board? 
// Related Topics Array Backtracking Matrix 
// 👍 7013 👎 274


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dfs
 * time: O(mn*4^L)，其中4是因为dfs往四个方向递归，L为字符串长度，递归层最深也就L
 * space: O(L)，递归栈采用的空间
 * */
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if(dfs(board, i, j, word, 0)){
                    return true;
                }
            }
        }
        return false;
    }

    int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int m, n;

    bool dfs(vector<vector<char>> &board, int x, int y, string &word, int idx) {
        if (idx == word.size()) {
            return true;
        }

        if (x < 0 || x >= m || y < 0 || y >=  n) {
            return false;
        }

        if (board[x][y] != word[idx]) {
            return false;
        }

        char c = board[x][y];
        board[x][y] = '#';
        bool res = false;

        for (auto dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            res = dfs(board, nx, ny, word, idx + 1);
            if (res) {
                break;
            }
        }

        board[x][y] = c;
        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
