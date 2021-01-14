/*
solution: DFS + binary search
time: O(n^2logn), n^2 for DFS, logn for bineray search
space: O(n^2)，stack space
*/
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return -1;
        int m = grid.size(), n = grid[0].size();
        // binary search
        int left = grid[0][0], right = 2500, mid, res;
        while (left< right) {
            mid = (left + right) / 2;
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            if (dfs(grid, visited, mid, 0, 0)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
    
private:
    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int max, int x, int y) {
        int m = grid.size(), n = grid[0].size();
        if (x == m - 1 && y == n - 1) return true;
        visited[x][y] = true;
        
        for (int k = 0; k < 4; k++) {
            int new_x = x + dir[k][0], new_y = y + dir[k][1];
            if (new_x < 0 || new_x >= grid.size() || new_y < 0 
                || new_y >= grid[0].size() || visited[new_x][new_y] || grid[new_x][new_y] > max)
                continue;
            if (dfs(grid, visited, max, new_x, new_y)) return true;
        }
        return false;
    }
};


