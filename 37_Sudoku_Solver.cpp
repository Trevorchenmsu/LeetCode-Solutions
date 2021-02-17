/*
solution 1: backtrack
time: unknown
space: unknown
*/
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        solve(board);
    }
    
    bool solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) return true;
                            else board[i][j] = '.';
                        } 
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c){
        for(int i = 0; i < 9; i++){
            if(board[i][col] == c) return false;
            if(board[row][i] == c) return false;
            if(board[i/3 + (row/3)*3][i%3 + (col/3)*3] == c){
                return false;
            }
        }
        return true;
    }
};