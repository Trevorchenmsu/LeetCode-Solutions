/*
Solution: backtracking
time: O(n*m*3^L), n is row, m is col. even though there are four directions for DFS, but one of the directions come
from the previous position, so we don't need to consider it. only 3 directions is considered.
space: O(L), the maximum length of the call stack would be the length of the word.
*/
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(search(board, word, 0, i, j)){
                    return true;
                }
            }
        }
        return false;
    }
    
    bool search(vector<vector<char>>& board, string word, int idx, int i, int j){
        if(idx == word.size()) return true;
        int m = board.size(), n = board[0].size();
        if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[idx]) return false;
        char c = board[i][j];
        board[i][j] = '#';
        bool res = search(board, word, idx + 1, i - 1, j) ||
                   search(board, word, idx + 1, i + 1, j) ||
                   search(board, word, idx + 1, i, j - 1) ||
                   search(board, word, idx + 1, i, j + 1);
        board[i][j] = c;
        return res;
    }
};


