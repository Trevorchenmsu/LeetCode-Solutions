//You are given an m x n binary matrix grid. An island is a group of 1's (repres
//enting land) connected 4-directionally (horizontal or vertical.) You may assume 
//all four edges of the grid are surrounded by water. 
//
// The area of an island is the number of cells with a value 1 in the island. 
//
// Return the maximum area of an island in grid. If there is no island, return 0
//. 
//
// 
// Example 1: 
//
// 
//Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,
//0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,
//0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]
//]
//Output: 6
//Explanation: The answer is not 11, because the island must be connected 4-dire
//ctionally.
// 
//
// Example 2: 
//
// 
//Input: grid = [[0,0,0,0,0,0,0,0]]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// m == grid.length 
// n == grid[i].length 
// 1 <= m, n <= 50 
// grid[i][j] is either 0 or 1. 
// 
// Related Topics Array Depth-First Search Breadth-First Search Union Find Matri
//x 
// 👍 7324 👎 166


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: union find, size version
 * time: O(mn)
 * space: O(mn)
 * */

class DSU {
    vector<int> parent;
    vector<int> size;
public:
    DSU (int N)
    {
        parent.resize(N);
        size.resize(N, 1);
        for (int i = 0; i < N; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    int union_func(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py) return size[px];

        if (size[px] <= size[py])
        {
            parent[px] = py;
            size[py] += size[px];
            return size[py];
        }
        else{
            parent[py] = px;
            size[px] += size[py];
            return size[px];
        }
    }

    int get_size(int node)
    {
        return size[find(node)];
    }
};

class Solution {
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        DSU dsu(m * n);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0) continue;
                res = max(res, connect(grid, i, j, dsu, m, n));
            }
        }

        return res;
    }

    int connect(vector<vector<int>>& grid, int i, int j, DSU &dsu, int m, int n){
        int cur = i * n + j;
        int res = dsu.get_size(cur);
        for (auto dir : dirs)
        {
            int x = i + dir[0], y = j + dir[1];
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0)
                continue;

            int neighbor = x * n + y;
            res = max(res, dsu.union_func(cur, neighbor));
        }
        return res;
    }
};

class DSU:
    def __init__(self, N):
        self.parent = [i for i in range(N)]
        self.size = [1] * N

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        px = self.find(x)
        py = self.find(y)
        if px == py: return self.size[px]

        if self.size[px] <= self.size[py]:
            self.parent[px] = py
            self.size[py] += self.size[px]
            return self.size[py]
        else:
            self.parent[py] = px
            self.size[px] += self.size[py]
            return self.size[px]

    def get_size(self, node):
        return self.size[self.find(node)]


class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        m, n, res = len(grid), len(grid[0]), 0
        dsu = DSU(m * n)
        dirs = [(1, 0), (-1, 0), (0, -1), (0, 1)]

        def connect(x, y):
            cur = x * n + y
            res = dsu.get_size(cur)
            for (dx, dy) in dirs:
                nx, ny = x + dx, y + dy
                if nx < 0 or nx >= m or ny < 0 or ny >= n or grid[nx][ny] == 0:
                    continue
                neighbor = nx * n + ny
                res = max(res, dsu.union(cur, neighbor))
            return res

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0: continue
                res = max(res, connect(i, j))

        return res
//leetcode submit region end(Prohibit modification and deletion)
