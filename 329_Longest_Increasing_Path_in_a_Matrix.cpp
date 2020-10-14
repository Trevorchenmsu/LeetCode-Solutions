/*
solution: DFS + memorization
time: O(m*n), m is row, n is column of matrix, since we traverse the whole matrix
space: O(m*n), new space for 2D arrays
*/
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int res = 0;
        // edge case
        if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0) {
            return res;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<vector<bool>> visited(m, vector<bool> (n));
        vector<vector<int>> memo(m, vector<int> (n));
        
        // dfs + memorization
        for (int i = 0; i < m ; ++i) {
            for (int j = 0; j < n; ++j) {
                res = max(res, dfs(matrix, i, j, visited, memo));
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& matrix,int x, int y, vector<vector<bool>>& visited, vector<vector<int>>& memo) {
        if (visited[x][y]) {
            return memo[x][y];
        }
        int direction[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        int m = matrix.size();
        int n = matrix[0].size();
        int res = 1;
        for (int k = 0; k < 4; ++k) {
            int nx = x + direction[k][0];
            int ny = y + direction[k][1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || matrix[nx][ny] <= matrix[x][y]) {
                continue;
            }
            res = max(res, 1 + dfs(matrix, nx, ny, visited, memo));
            
        }
        visited[x][y] = true;
        memo[x][y] = res;
        
        return res;
    }
};