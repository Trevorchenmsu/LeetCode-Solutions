/*
solution 1: backtrack
time: O(9^(9*9))
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

/*
solution 2: backtrack + hashtable
time: O(9^(9*9))
space: unknown
*/
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // update three hashtables
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') 
                    spaces.emplace_back(i, j);
                else {
                    int curNum = board[i][j] - '0';
                    row[i][curNum] = col[j][curNum] = box[j/3 + (i/3)*3][curNum] = 1;
                }
            }
        }
        
        backtrack(board, 0);
    }
    
private:
    int row[9][10] = {0};
    int col[9][10] = {0};
    int box[9][10] = {0};
    vector<pair<int, int>> spaces;    
    
    bool backtrack(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) 
            return true;

        auto [i, j] = spaces[pos];
        for (int curNum = 1; curNum <= 9; curNum++) {
            if (row[i][curNum] || col[j][curNum] || box[j/3 + (i/3)*3][curNum])
                continue;
            row[i][curNum] = col[j][curNum] = box[j/3 + (i/3)*3][curNum] = 1;
            board[i][j] = curNum + '0';
            if(backtrack(board, pos + 1)) 
                return true;
            row[i][curNum] = col[j][curNum] = box[j/3 + (i/3)*3][curNum] = 0;
        }
        return false;
    }
};