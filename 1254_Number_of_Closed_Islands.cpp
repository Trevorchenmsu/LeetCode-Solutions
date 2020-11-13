/*
solution: DFS
time: O(m*n), m is row, n is column
space: O(m*n), the worst case is go to the deepest stack, which means consider each point in the matrix
*/

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;
        // edge case
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0)
            return res;
        
        // traverse the whole grid
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] ==  0) {
                    res += dfs(grid, i, j) ? 1 : 0;
                }
            }
        }
        return res;
    }

private: 
    bool dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return false;
        if (grid[i][j] == 1)
            return true;
        grid[i][j] = 1;
        
        bool up = dfs(grid, i - 1, j);
        bool down = dfs(grid, i + 1, j);
        bool left = dfs(grid, i, j - 1);
        bool right = dfs(grid, i, j + 1);
        
        return up && down && left && right;
    }
};

/*
solution: DFS
time: O(m*n), m is row, n is column
space: O(m*n), the worst case is all the elements are 0.
*/
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return res;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool> (n));
        
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] || visited[i][j])
                    continue;
                res += bfs(grid, visited, i, j) ? 1 : 0;
            }
        }
        return res;
    }
    
    bool bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j) {
        queue<pair<int, int>> q;
        q.push({i, j});
        bool res = true;
        
        while (!q.empty()) {
            pair<int, int> cur = q.front(); q.pop();
            for (auto dir : directions) {
                int x = cur.first + dir.first;
                int y = cur.second + dir.second;
                if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
                    res = false;
                    continue;
                }
                if (visited[x][y] || grid[x][y])
                    continue;
                q.push({x, y});
                visited[x][y] = true;
            }
        }
        return res;
    }
    
private:
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};