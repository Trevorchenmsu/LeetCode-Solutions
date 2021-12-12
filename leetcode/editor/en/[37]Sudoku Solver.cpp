//Write a program to solve a Sudoku puzzle by filling the empty cells. 
//
// A sudoku solution must satisfy all of the following rules: 
//
// 
// Each of the digits 1-9 must occur exactly once in each row. 
// Each of the digits 1-9 must occur exactly once in each column. 
// Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes
// of the grid. 
// 
//
// The '.' character indicates empty cells. 
//
// 
// Example 1: 
//
// 
//Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5"
//,".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".","."
//,".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".","."
//,"6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"
//],[".",".",".",".","8",".",".","7","9"]]
//Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4
//","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3
//"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],[
//"9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3",
//"4","5","2","8","6","1","7","9"]]
//Explanation: The input board is shown above and the only valid solution is sho
//wn below:
//
//
// 
//
// 
// Constraints: 
//
// 
// board.length == 9 
// board[i].length == 9 
// board[i][j] is a digit or '.'. 
// It is guaranteed that the input board has only one solution. 
// 
// Related Topics Array Backtracking Matrix 
// 👍 3820 👎 124


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: naive backtrack
 * time: O(9^(n^2))？,n为格子长度，格子长度为9
 * space: O(n^2)？，只有三个额外储存的哈希表才需要额外空间，每个需要O(81)=O(1)
 * */
class Solution {
public:
    vector<unordered_set<char>> row = vector<unordered_set<char>> (9);
    vector<unordered_set<char>> col = vector<unordered_set<char>> (9);
    vector<unordered_set<char>> box = vector<unordered_set<char>> (9);
    void solveSudoku(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }

        // 存储表中已采用过的元素，从行/列/box三种情况考虑
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }

                row[i].insert(board[i][j]);
                col[j].insert(board[i][j]);
                box[(i/3)*3 + j/3].insert(board[i][j]);
            }
        }
        search(board, 0);
    }

    bool search(vector<vector<char>>& board, int index) {
        if (index == 81) {
            return true;
        }

        int i = index / 9, j = index % 9;
        if (board[i][j] != '.') {
            return search(board, index + 1);;
        }

        for (int val = 1; val < 10; val++) {
            char c = val + '0';
            if (!isValid(i, j, c)) {
                continue;
            }

            board[i][j] = c;
            row[i].insert(c);
            col[j].insert(c);
            box[(i/3)*3 + j/3].insert(c);

            if (search(board, index + 1)){
                return true;
            }

            row[i].erase(c);
            col[j].erase(c);
            box[(i/3)*3 + j/3].erase(c);
            board[i][j] = '.';
        }

        return false;
    }

    bool isValid(int i, int j, char c) {
        if (row[i].find(c) != row[i].end()) {
            return false;
        }
        if (col[j].find(c) != col[j].end()) {
            return false;
        }
        if (box[(i/3)*3 + j/3].find(c) != box[(i/3)*3 + j/3].end()) {
            return false;
        }
        return true;
    }
};


/*
 * solution 2: backtrack
 * time: O(9^(n^2))？,n为格子长度，格子长度为9
 * space: O(n^2)？，只有三个额外储存的哈希表才需要额外空间，每个需要O(81)=O(1)
 * */

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }

        search(board, 0);
    }

    bool search(vector<vector<char>>& board, int index) {
        if (index == 81) {
            return true;
        }

        int i = index / 9, j = index % 9;
        if (board[i][j] != '.') {
            return search(board, index + 1);;
        }

        for (int val = 1; val < 10; val++) {
            char c = val + '0';
            if (!isValid(board, i, j, c)) {
                continue;
            }

            board[i][j] = c;
            if (search(board, index + 1)){
                return true;
            }
            board[i][j] = '.';
        }

        return false;
    }

    bool isValid(vector<vector<char>>& board, int x, int y, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[x][i] == c) {
                return false;
            }
            if (board[i][y] == c) {
                return false;
            }
            // box的坐标转化比较tricky
            if (board[(x/3)*3 + i/3][(y/3)*3 + i%3] == c) {
                return false;
            }
        }

        return true;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
