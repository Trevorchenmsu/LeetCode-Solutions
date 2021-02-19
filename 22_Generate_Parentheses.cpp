/*
solution: backtrack
time: O(4^n/n^0.5)
space: O(n), the recursive maximum is O(2n)
*/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if (n == 0) return res;
        string path = "";
        backtrack(res, path, n, n);
        return res;
    }
    
    void backtrack(vector<string> &res, string path, int left, int right) {
        if (left > right)
            return;
        
        if (left == 0 && right == 0) {
            res.push_back(path);
            return;
        }
        
        if (left > 0) 
            backtrack(res, path + "(", left - 1, right);
           
        if (right > 0) 
            backtrack(res, path + ")", left, right - 1);
            
    }
};