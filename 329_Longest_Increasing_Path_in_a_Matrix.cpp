/*
solution: DFS + memorization
time: O(mn), m is row, n is column. Each vertex/edge will be visited once only. The total time
complexity is O(V+E), where V is the total number of vertices and E is the total number of edges.
In this problem, one vertex can traverse to four directions, so O(E)=O(4V)=O(mn).
space: O(mn), we build memo and visited 2D array to store the result.
*/
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int res = 0;
        // corner case
        if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0)
            return res;
        
        m = matrix.size(), n = matrix[0].size();
        
        vector<vector<bool>> visited(m, vector<bool> (n));
        vector<vector<int>> memo(m, vector<int> (n));
        
        // dfs + memorization
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res = max(res, dfs(matrix, i, j, visited, memo));
            }
        }
        
        return res;
    }
    
    int dfs(const vector<vector<int>>& matrix, int x, int y, 
            vector<vector<bool>>& visited, vector<vector<int>>& memo) {
        if (visited[x][y])
            return memo[x][y];
        
        int res = 1;
        
        for (int d = 0; d < 4; ++d) {
            int new_x = x + dir[d][0];
            int new_y = y + dir[d][1];
            if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n || matrix[x][y] >= matrix[new_x][new_y])
                continue;
            res = max(res, 1 + dfs(matrix, new_x, new_y, visited, memo));
        }
        
        visited[x][y] = true;
        memo[x][y] = res;
        
        return res;
    }
    
private:
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m, n;
};