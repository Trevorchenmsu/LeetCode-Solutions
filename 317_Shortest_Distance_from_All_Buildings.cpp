/*
solution: BFS+DP
time: O(m*n*m*n), m is row, n is col.
space: O(m*n)
*/

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty())
            return -1;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist (m, vector<int> (n));
        vector<vector<int>> nums (m, vector<int> (n));
        int numBuild = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    ++numBuild;
                    bfs(grid, i, j, dist, nums);
                }
            }
        }
        
        int res = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && dist[i][j] != 0 && nums[i][j] == numBuild) {
                    res = min(res, dist[i][j]);
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
    
    void bfs(const vector<vector<int>>& grid, int row, int col, 
             vector<vector<int>>& dist, vector<vector<int>>& nums) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        q.push({row, col});
        vector<vector<bool>> visited (m, vector<bool> (n));
        int distance = 0;
        
        while (!q.empty()) {
            ++distance;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                pair<int, int> cur = q.front(); q.pop();
                for (int j = 0; j < 4; ++j) {
                    int new_x = cur.first + dir[j][0];
                    int new_y = cur.second + dir[j][1];
                    if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n || 
                        grid[new_x][new_y] != 0 || visited[new_x][new_y])
                        continue;
                    visited[new_x][new_y] = true;
                    dist[new_x][new_y] += distance;
                    ++nums[new_x][new_y];
                    q.push({new_x, new_y});
                }
            }
        }
    }
    
private:
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};