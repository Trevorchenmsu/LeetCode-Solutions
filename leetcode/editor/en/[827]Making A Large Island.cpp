//You are given an n x n binary matrix grid. You are allowed to change at most o
//ne 0 to be 1. 
//
// Return the size of the largest island in grid after applying this operation. 
//
//
// An island is a 4-directionally connected group of 1s. 
//
// 
// Example 1: 
//
// 
//Input: grid = [[1,0],[0,1]]
//Output: 3
//Explanation: Change one 0 to 1 and connect two 1s, then we get an island with 
//area = 3.
// 
//
// Example 2: 
//
// 
//Input: grid = [[1,1],[1,0]]
//Output: 4
//Explanation: Change the 0 to 1 and make the island bigger, only one island wit
//h area = 4. 
//
// Example 3: 
//
// 
//Input: grid = [[1,1],[1,1]]
//Output: 4
//Explanation: Can't change any 0 to 1, only one island with area = 4.
// 
//
// 
// Constraints: 
//
// 
// n == grid.length 
// n == grid[i].length 
// 1 <= n <= 500 
// grid[i][j] is either 0 or 1. 
// Related Topics Array Depth-First Search Breadth-First Search Union Find Matri
//x 
// 👍 1891 👎 46


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: union find，哈希表去重
 * time: O(mn)
 * space: O(mn)
 * */
class DSU{
public:
    vector<int> parents, size;
    DSU(int N) {
        parents = vector<int> (N, 0);
        size = vector<int> (N, 1);
        for (size_t i = 0; i < N; i++)  parents[i] = i;
    }
    int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }
    void unionFunc(int x, int y) {
        int root_x = find(x), root_y = find(y);
        if (root_x == root_y) return;
        if (size[root_x] <= size[root_y]) {
            parents[root_x] = root_y;
            size[root_y] += size[root_x];
        }
        else {
            parents[root_y] = root_x;
            size[root_x] += size[root_y];
        }
    }
};


class Solution {
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 1;
        DSU dsu = DSU(m * n);

        /*  主体思想：
         * (1)先通过UF把所有连通块都合并，同时采用size版本得到每个连通块的size。这样，在某个连通块上的点，可以通过find找到
         *  它的root，再通过size就可以找到这个点在所属连通块上的size。也就是相当于对连通块的点的值都进行了更新，每个点都具有该大块的size。
         *  非常高效，因为我们实际上并不需要去生成这样的矩阵，只需要查找就行了，find和size函数操作为O(1).
         * (2)得到上面的matrix后，在matrix中查找0的点进行翻牌。假如我们遇到了一个0点，对它翻牌后，它的4个方向邻居都得考虑，如果邻居有效的话
         * 表示通过翻牌以后我们可以把有效的连通块结合起来，所以我们可以通过邻居，用find查找它的根，再用size去查找根对应的连通块大小，期间用哈希表
         * 把对应的连通块root和size用哈希表存起来。这里必须用哈希表，可以对root进行去重，因为不同邻居可能在相同的连通块。当考虑完四个方向后，
         * 再对哈希表进行求和，求和的意思就相等于把这些块链接起来形成一个更大的块。由于本身这个点的面积也算1，所以cnt初始化为1。
         * */

        // 先通过UF更新每个root下对应的size，同时找出最大块的size，即res
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    for (auto &dir : dirs) {
                        int x = i + dir[0], y = j + dir[1];
                        if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == 0)
                            continue;
                        dsu.unionFunc(i * n + j, x * n + y);
                        // size版本的UF会将小块的size并入大块的size，所以这里采用(i,j)，因为它考虑4个方向，会累积，比(x,y)多
                        res = max(res, dsu.size[dsu.find(i * n + j)]);
                    }
                }
            }
        }

        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    //这里必须要用哈希表把parent存起来，不能直接用cnt在for循环里面累加
                    // 因为4个方向的邻居可能是同个连通块，不用哈希表的话就会重复计算size
                    unordered_map<int, int> parent2size;
                    for (auto &dir : dirs) {
                        int x = i + dir[0], y = j + dir[1];
                        if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == 0)
                            continue;
                        int parent = dsu.find(x * n + y);
                        parent2size[parent] = dsu.size[parent];
                    }
                    int cnt = 1;
                    for (auto &ps : parent2size) {
                        cnt += ps.second;
                    }
                    res = max(res, cnt);
                }
            }
        }

        return res;
    }
};

/*
 * solution 2: union find，哈希集去重，节省遍历次数
 * time: O(mn)
 * space: O(mn)
 * */

class DSU {
    vector<int> parent, size;
public:
    DSU (int N)
    {
        parent.resize(N);
        size.resize(N, 1);
        for (int i = 0; i < N; ++i) parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void union_func(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (size[px] <= size[py])
        {
            parent[px] = py;
            size[py] += size[px];
        }
        else
        {
            parent[py] = px;
            size[px] += size[py];
        }
    }

    int get_size(int node)
    {
        return size[find(node)];
    }

};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        DSU dsu(m * n);
        int res = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 0) continue;
                res = max(res, dsu.get_size(dsu.find(i * n + j)));
                for (auto dir : dirs)
                {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0)
                        continue;
                    int cur = i * n + j;
                    int neighbor = nx * n + ny;
                    dsu.union_func(cur, neighbor);
                }
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1) continue;
                unordered_set<int> visited;
                int count = 1;
                for (auto dir : dirs)
                {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0)
                        continue;
                    int parent = dsu.find(nx * n + ny);
                    auto it = visited.find(parent);
                    if (it != visited.end()) continue;
                    count += dsu.get_size(parent);
                    visited.insert(parent);
                }
                res = max(res, count);
            }
        }

        return res;
    }
};

/*
 * solution 3: dfs, TLE
 * time: O(mn*mn)
 * space: O(mn)
 * */

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        bool hasZero = false;

        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (grid[i][j] == 1) continue;
                grid[i][j] = 1;
                vector<vector<int>> visited(m, vector<int> (n, 0));
                res = max(res, dfs(grid, i, j, visited));
                if (res == m * n) return res;
                grid[i][j] = 0;
                hasZero = true;
            }
        }

        return hasZero ? res : m * n;
    }

    int dfs(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &visited) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return 0;
        if (grid[i][j] == 0 || visited[i][j]) return 0;
        visited[i][j] = 1;

        int area = 1 + dfs(grid, i + 1, j, visited) +
                   dfs(grid, i - 1, j, visited) +
                   dfs(grid, i, j + 1, visited) +
                   dfs(grid, i, j - 1, visited);
        return area;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
