//You are given an n x n binary matrix grid where 1 represents land and 0 repres
//ents water. 
//
// An island is a 4-directionally connected group of 1's not connected to any ot
//her 1's. There are exactly two islands in grid. 
//
// You may change 0's to 1's to connect the two islands to form one island. 
//
// Return the smallest number of 0's you must flip to connect the two islands. 
//
// 
// Example 1: 
//
// 
//Input: grid = [[0,1],[1,0]]
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
//Output: 2
// 
//
// Example 3: 
//
// 
//Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// n == grid.length == grid[i].length 
// 2 <= n <= 100 
// grid[i][j] is either 0 or 1. 
// There are exactly two islands in grid. 
// 
// Related Topics Array Depth-First Search Breadth-First Search Matrix 
// 👍 2010 👎 116


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dfs + bfs
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int shortestBridge(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<vector<int>> q;
        vector<vector<int>> visited(m, vector<int> (n, 0));
        bool found = false;

        // O(mn)
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (!found && grid[i][j] == 1) {
                    dfs(grid, visited, i, j, q);
                    found = true;
                    break;
                }
            }
        }

        // O(mn)
        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                for (auto &dir : dirs) {
                    int x = cur[0] + dir[0], y = cur[1] + dir[1];
                    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y])
                        continue;

                    if (grid[x][y] == 1)
                        return step;

                    q.push({x, y});
                    visited[x][y] = 1;
                }
            }
            step++;
        }

        return -1;
    }

    void dfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int i, int j, queue<vector<int>> &q) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || visited[i][j] || grid[i][j] == 0)
            return;
        visited[i][j] = 1;
        q.push({i, j});
        for (auto &dir : dirs) {
            int x = i + dir[0], y = j + dir[1];
            dfs(grid, visited, x, y, q);
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
