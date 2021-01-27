/*
solution 1: brute force + bismask
time: (2^(m*n)*5*(m*n))
space: O(1)
*/

class Solution {
public:
    int m, n;
    int minFlips(vector<vector<int>>& mat) {
        m = mat.size(), n = mat[0].size();
        int res = INT_MAX;
        
        for (int state = 0; state < (1 << m * n); state++) {
            if (check(mat, state))
                res = min(res, (int)bitset<9>(state).count());
        }
        return res == INT_MAX ? -1 : res;
    }
    
    bool check(vector<vector<int>>& mat, int state) {
        int dirs[5][2] = {{0, 0}, {0, 1}, {0 ,-1}, {1, 0}, {-1 ,0}};
        auto temp = mat;
        for (int b = 0; b < m * n; b++) {
            int t = state % 2;
            if (t == 0) continue;
            state /= 2;
            
            int i = b / n;
            int j = b % n;
            
            for (auto dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];
                
                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                temp[x][y] = 1 - temp[x][y];
            }
        }
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (temp[i][j] != 0) return false;
        
        return true;
    }
};

