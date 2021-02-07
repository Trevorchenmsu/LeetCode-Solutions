/*
solution: backtrack
time: O(n!)
space: O(n!)
*/
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> col; // store the column location of queen in each row
        backtrack(res, col, n);
        return res;
    }
    
private:    
    void backtrack(vector<vector<string>> &res, vector<int> &col, int n) {
        if (col.size() == n) {
            res.push_back(getSolution(col));
            return;
        }
        
        for (int i = 0; i < n; i++) {
            if (!isValid(col, i))
                continue;
            col.push_back(i);
            backtrack(res, col, n);
            col.pop_back();
        }
    }
    
    vector<string> getSolution(vector<int>& col) {
        vector<string> res;
        int n = col.size();
        for (int i = 0; i < n; i++) {
            string row(n, '.');
            row[col[i]] = 'Q';
            res.push_back(row);
        }
        return res;
    }
     
    bool isValid(vector<int>& col, int curCol) {
        int row = col.size();
        for (int j = 0; j < row; j++) {
            // queens in the same column or in the diagonal direction 
            if (curCol == col[j] || abs(curCol - col[j]) == abs(j - row))
                return false;
        }
        return true;
    }
};
