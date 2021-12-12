//You are given row x col grid representing a map where grid[i][j] = 1 represent
//s land and grid[i][j] = 0 represents water. 
//
// Grid cells are connected horizontally/vertically (not diagonally). The grid i
//s completely surrounded by water, and there is exactly one island (i.e., one or 
//more connected land cells). 
//
// The island doesn't have "lakes", meaning the water inside isn't connected to 
//the water around the island. One cell is a square with side length 1. The grid i
//s rectangular, width and height don't exceed 100. Determine the perimeter of the
// island. 
//
// 
// Example 1: 
//
// 
//Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
//Output: 16
//Explanation: The perimeter is the 16 yellow stripes in the image above.
// 
//
// Example 2: 
//
// 
//Input: grid = [[1]]
//Output: 4
// 
//
// Example 3: 
//
// 
//Input: grid = [[1,0]]
//Output: 4
// 
//
// 
// Constraints: 
//
// 
// row == grid.length 
// col == grid[i].length 
// 1 <= row, col <= 100 
// grid[i][j] is 0 or 1. 
// There is exactly one island in grid. 
// 
// Related Topics Array Depth-First Search Breadth-First Search Matrix 
// 👍 3811 👎 219


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs
 * time: O(V+E) = O(mn)
 * space: O(V) = O(mn)
 * */
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return dfs(grid, i, j);
                }
            }
        }

        return 0;
    }

    int dfs(vector<vector<int>> &grid, int x, int y) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0) {
            return 1;
        }

        if (grid[x][y] == -1) {
            return 0;
        }

        grid[x][y] = -1;

        return dfs(grid, x + 1, y) + dfs(grid, x - 1, y) + dfs(grid, x, y + 1) + dfs(grid, x, y - 1);
    }
};

/*
 * solution 1: math
 * time: O(V+E) = O(mn)
 * space: O(1）
 * */
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    res += 4; // 每个grid有条边
                    if (i + 1 < m && grid[i + 1][j] == 1) res -= 2; //往下看，相邻都是岛，减少两边条
                    if (j + 1 < n && grid[i][j + 1] == 1) res -= 2; //往右看，相邻都是岛，减少两边条
                }
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
