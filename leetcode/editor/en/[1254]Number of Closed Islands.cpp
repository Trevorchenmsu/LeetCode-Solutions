//Given a 2D grid consists of 0s (land) and 1s (water). An island is a maximal 4
//-directionally connected group of 0s and a closed island is an island totally (a
//ll left, top, right, bottom) surrounded by 1s. 
//
// Return the number of closed islands. 
//
// 
// Example 1: 
//
// 
//
// 
//Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,
//0,1,0,1],[1,1,1,1,1,1,1,0]]
//Output: 2
//Explanation: 
//Islands in gray are closed because they are completely surrounded by water (gr
//oup of 1s). 
//
// Example 2: 
//
// 
//
// 
//Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: grid = [[1,1,1,1,1,1,1],
//               [1,0,0,0,0,0,1],
//               [1,0,1,1,1,0,1],
//               [1,0,1,0,1,0,1],
//               [1,0,1,1,1,0,1],
//               [1,0,0,0,0,0,1],
//               [1,1,1,1,1,1,1]]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= grid.length, grid[0].length <= 100 
// 0 <= grid[i][j] <=1 
// 
// Related Topics Array Depth-First Search Breadth-First Search Union Find Matri
//x 
// 👍 1328 👎 34


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (grid[i][j] == 0 && dfs(grid, i, j)) {
                    res++;
                }
            }
        }

        return res;
    }

    bool dfs(vector<vector<int>>& grid, int x, int y) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) return false;
        if (grid[x][y] == 1) return true; // 遇到1要返回true，表示遇到了水的边界，符合close island的要求
        grid[x][y] = 1;

        // 注意到这里要用&而不能用&&，因为&&会短路后面的递归，当一个不满足要求后就不会判定后面的情况，会导致某些连通区域没有被标注。
        return dfs(grid, x + 1, y) &
               dfs(grid, x - 1, y) &
               dfs(grid, x, y + 1) &
               dfs(grid, x, y - 1);

        // 或者采用下面这种方式，可以保证四个方向都递归到。
//        bool down = dfs(grid, x + 1, y);
//        bool up = dfs(grid, x - 1, y);
//        bool right = dfs(grid, x, y + 1);
//        bool left = dfs(grid, x, y - 1);
//
//        return down && up && right && left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
