/*
solution: two pointers
time: O(n*m*(m+n)*k), n is row, m is column, k is the round
space: O(1)
*/
class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {    
        int n = board.size(), m = board[0].size();
        
        // search the valid candy block and mark the candy
        bool found = true;
        while (found) {
            found = false;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    int val = abs(board[i][j]);
                    if (val == 0) continue;
                    // horizontal
                    if (j < m - 2 && abs(board[i][j + 1]) == val && abs(board[i][j + 2]) == val) {
                        found = true;
                        int idx = j;
                        while(idx < m && abs(board[i][idx]) == val) {
                            board[i][idx++] = -val;
                        }
                    }
                    // vertical
                    if (i < n - 2 && abs(board[i + 1][j]) == val && abs(board[i + 2][j]) == val) {
                        found = true;
                        int idx = i;
                        while(idx < n && abs(board[idx][j]) == val) {
                            board[idx++][j] = -val;
                        }
                    }
                }
            }
            
            if (found) {
                for (int j = 0; j < m; ++j) {
                    int storeIdx = n - 1;  
                    for (int i = n - 1; i >= 0; --i) {
                        if (board[i][j] > 0) {
                            board[storeIdx--][j] = board[i][j];
                        }

                    } 
                    for (int k = storeIdx; k >= 0; --k) {
                        board[k][j] = 0;
                    }

                }
            }
          
        }
        
        return board;
    }
};
