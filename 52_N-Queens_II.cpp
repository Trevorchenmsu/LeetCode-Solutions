/*
solution: backtrack
time: O(n!)
space: O(n!)
*/
class Solution {
public:
    int totalNQueens(int n) {
        int res = 0;
        vector<int> col;
        backtrack(res, col, n);
        return res;
    }
    
    void backtrack(int& res, vector<int>& col, int n) {
        if (col.size() == n) {
            res++;
            return;
        }
        
        for (int i = 0; i < n; i++) {
            if (!isValid(col, i)) continue;
            col.push_back(i);
            backtrack(res, col, n);
            col.pop_back();
        }
    }
    
    bool isValid(vector<int>& col, int curCol) {
        int row = col.size();
        for (int i = 0; i < row; i++) {
            if (col[i] == curCol || abs(col[i] - curCol) == abs(i - row))
                return false;
        }        
        return true;
    }
};