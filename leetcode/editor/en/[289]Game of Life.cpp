//According to Wikipedia's article: "The Game of Life, also known simply as Life
//, is a cellular automaton devised by the British mathematician John Horton Conwa
//y in 1970." 
//
// The board is made up of an m x n grid of cells, where each cell has an initia
//l state: live (represented by a 1) or dead (represented by a 0). Each cell inter
//acts with its eight neighbors (horizontal, vertical, diagonal) using the followi
//ng four rules (taken from the above Wikipedia article): 
//
// 
// Any live cell with fewer than two live neighbors dies as if caused by under-p
//opulation. 
// Any live cell with two or three live neighbors lives on to the next generatio
//n. 
// Any live cell with more than three live neighbors dies, as if by over-populat
//ion. 
// Any dead cell with exactly three live neighbors becomes a live cell, as if by
// reproduction. 
// 
//
// The next state is created by applying the above rules simultaneously to every
// cell in the current state, where births and deaths occur simultaneously. Given 
//the current state of the m x n grid board, return the next state. 
//
// 
// Example 1: 
//
// 
//Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
//Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
// 
//
// Example 2: 
//
// 
//Input: board = [[1,1],[1,0]]
//Output: [[1,1],[1,1]]
// 
//
// 
// Constraints: 
//
// 
// m == board.length 
// n == board[i].length 
// 1 <= m, n <= 25 
// board[i][j] is 0 or 1. 
// 
//
// 
// Follow up: 
//
// 
// Could you solve it in-place? Remember that the board needs to be updated simu
//ltaneously: You cannot update some cells first and then use their updated values
// to update other cells. 
// In this question, we represent the board using a 2D array. In principle, the 
//board is infinite, which would cause problems when the active area encroaches up
//on the border of the array (i.e., live cells reach the border). How would you ad
//dress these problems? 
// 
// Related Topics Array Matrix Simulation 
// 👍 2933 👎 358


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: state machine
 * time: O(mn)
 * space: O(1)
 *
 * */
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = counter(board, i, j);
                if (board[i][j] == 1 && (cnt < 2 || cnt > 3)) {
                    // 2 represents state changes from 1 to 0
                    board[i][j] = 2;
                }
                else if (board[i][j] == 0 && cnt == 3) {
                    // 3 represents state changes from 0 to 1
                    board[i][j] = 3;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] %= 2;
            }
        }

    }

private:
    int dirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
                      {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    int m, n;

    int counter(vector<vector<int>> &board, int x, int y) {
        int cnt = 0;
        for (auto &dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }

            if (board[nx][ny] == 1 || board[nx][ny] == 2) {
                cnt++;
            }
        }

        return cnt;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
