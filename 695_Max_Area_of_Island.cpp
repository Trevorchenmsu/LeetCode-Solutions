/*
solution 1: dfs
time: O(n*n)
space: O(n*n), the space used by the call stack during our recursion.
*/
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res = 0; 
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return res;
        }
        
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 1) {
                    res = max(res, dfs(grid, i, j));
                }
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j) {
        int res = 0;
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0) {
            return res;
        }
        grid[i][j] = 0;
        
        int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        
        for (int k = 0; k < 4; ++k) {
            int nx = i + dir[k][0];
            int ny = j + dir[k][1];
            res += dfs(grid, nx, ny);
        }
        
        return res + 1;
    }
};

/*
solution 2: bfs
time: O(n*n)
space: O(n*n), the space used by the call stack during our recursion.
*/
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res = 0; 
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return res;
        }
        
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 1) {
                    res = max(res, bfs(grid, i, j));
                }
            }
        }
        return res;
    }
    
    int bfs(vector<vector<int>>& grid, int x, int y) {
        pair<int, int> cur = {x, y};
        queue<pair<int, int>> q;
        set<pair<int, int>> visited;
        q.push(cur);
        visited.insert(cur);
        int res = 1;
        
        int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            
            for (int k = 0; k < 4; ++k) {
                int nx = curr.first + dir[k][0];
                int ny = curr.second + dir[k][1];
                if (isValid(nx, ny, visited, grid)) {
                    q.push({nx, ny});
                    visited.insert({nx, ny});
                    grid[curr.first][curr.second] = 0;
                    ++res;
                }
            }
        }
        return res;
    }
    
    bool isValid(int x, int y,  set<pair<int, int>>& visited, vector<vector<int>>& grid) {
        if (x < 0 || x >= grid.size()) {
            return false;
        }
        if (y < 0 || y >= grid[0].size()) {
            return false;
        }
        if (grid[x][y] == 0 || visited.find({x, y}) != visited.end()) {
            return false;
        }
        return true;
    }
};

/*
solution 3: union find
time: O(n*n)
space: O(n*n), the space used by the call stack during our recursion.
*/