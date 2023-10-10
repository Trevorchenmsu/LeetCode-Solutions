//Given an m x n 2D binary grid grid which represents a map of '1's (land) and '
//0's (water), return the number of islands. 
//
// An island is surrounded by water and is formed by connecting adjacent lands h
//orizontally or vertically. You may assume all four edges of the grid are all sur
//rounded by water. 
//
// 
// Example 1: 
//
// 
//Input: grid = [
//  ["1","1","1","1","0"],
//  ["1","1","0","1","0"],
//  ["1","1","0","0","0"],
//  ["0","0","0","0","0"]
//]
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: grid = [
//  ["1","1","0","0","0"],
//  ["1","1","0","0","0"],
//  ["0","0","1","0","0"],
//  ["0","0","0","1","1"]
//]
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// m == grid.length 
// n == grid[i].length 
// 1 <= m, n <= 300 
// grid[i][j] is '0' or '1'. 
// 
// Related Topics Array Depth-First Search Breadth-First Search Union Find Matri
//x 
// 👍 12449 👎 311


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: union find, simple version with path compression
 * time: O(mn)
 * space: O(mn)
 *
 * */

class DSU {
    vector<int> parent;
public:
    DSU(int N)
    {
        parent.resize(N);
        for (int i = 0; i < N; ++i)
            parent[i] = i;
    }

    // path compression
    int find(int x)
    {
        // 不相等表示上面有parent，通过find查找再上一级的parent
        // 把找到的parent赋给当前x的parent
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_func(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        parent[px] = py;
    }
};

/*
 * solution 2: union find, rank version
 * */
class DSU {
    vector<int> parents, rank;
public:
    DSU(int N) {
        parents.resize(N);
        rank.resize(N, 1);
        for (int i = 0; i < N; i++) parents[i] = i;
    }

    int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    void union_func(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (rank[px] < rank[py]) {
            parents[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parents[py] = px;
        }
        else { // x和y调换也行，反正它们的rank相等
            parents[px] = py;
            rank[py]++;
        }
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int num_islands = 0;
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0)
            return num_islands;

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = grid.size(), n = grid[0].size();
        DSU dsu = DSU(m * n);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '0')
                {
                    continue;
                }

                ++num_islands;
                for (auto dir : dirs)
                {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == '0')
                        continue;

                    int node1 = dsu.find(i * n + j);
                    int node2 = dsu.find(nx * n + ny);
                    if (node1 != node2)
                    {
                        dsu.union_func(node1, node2);
                        --num_islands;
                    }
                }
            }
        }

        return num_islands;
    }
};


class DSU:
    def __init__(self, N):
        self.parent = [i for i in range(N)]

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])

        return self.parent[x]

    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        self.parent[px] = py


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        num_island = 0
        dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        dsu = DSU(m * n)

        for i in range(m):
            for j in range(n):
                if grid[i][j] == '0': continue
                num_island += 1

                for dir in dirs:
                    x, y = i + dir[0], j + dir[1]
                    if x < 0 or x >= m or y < 0 or y >= n or grid[x][y] == '0':
                        continue
                    cur = dsu.find(i * n + j)
                    neighbor = dsu.find(x * n + y)
                    if cur != neighbor:
                        dsu.union(cur, neighbor)
                        num_island -= 1

        return num_island

//leetcode submit region end(Prohibit modification and deletion)
