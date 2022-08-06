//You are given an empty 2D binary grid grid of size m x n. The grid represents 
//a map where 0's represent water and 1's represent land. Initially, all the cells
// of grid are water cells (i.e., all the cells are 0's). 
//
// We may perform an add land operation which turns the water at position into a
// land. You are given an array positions where positions[i] = [ri, ci] is the pos
//ition (ri, ci) at which we should operate the ith operation. 
//
// Return an array of integers answer where answer[i] is the number of islands a
//fter turning the cell (ri, ci) into a land. 
//
// An island is surrounded by water and is formed by connecting adjacent lands h
//orizontally or vertically. You may assume all four edges of the grid are all sur
//rounded by water. 
//
// 
// Example 1: 
//
// 
//Input: m = 3, n = 3, positions = [[0,0],[0,1],[1,2],[2,1]]
//Output: [1,1,2,3]
//Explanation:
//Initially, the 2d grid is filled with water.
//- Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land. We ha
//ve 1 island.
//- Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land. We st
//ill have 1 island.
//- Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land. We ha
//ve 2 islands.
//- Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land. We ha
//ve 3 islands.
// 
//
// Example 2: 
//
// 
//Input: m = 1, n = 1, positions = [[0,0]]
//Output: [1]
// 
//
// 
// Constraints: 
//
// 
// 1 <= m, n, positions.length <= 104 
// 1 <= m * n <= 104 
// positions[i].length == 2 
// 0 <= ri < m 
// 0 <= ci < n 
// 
//
// 
// Follow up: Could you solve it in time complexity O(k log(mn)), where k == pos
//itions.length? 
// Related Topics Array Union Find 
// 👍 1267 👎 35


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: union find, UF模板题
 * time: O(mn + k)，mn发生在初始化岛屿的位置，因为路径压缩union和find的操作为O(1)。
 * space: O(mn)
 * */

// disjoint set union, basic template
class DSU {
    vector<int> parents;
public:
    DSU(int N) {
        parents = vector<int> (N, 0);
        for (size_t i = 0; i < N; i++) {
            parents[i] = i;
        }
    }
    // path compression
    int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    void unionFunc(int x, int y) {
        parents[find(x)] =find(y);
    }
};

// 采用rank优化，大rank作为parent
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

    void unionFunc(int x, int y) {
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

// 采用size优化，大size作为parent，注意跟rank的区别，判定是加等号的
class DSU{
    vector<int> parents, size;
public:
    DSU(int N) {
        parents = vector<int> (N, 0);
        size = vector<int> (N, 1);
        for (size_t i = 0; i < N; i++) parents[i] = i;
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

/*
 * solution 3: union find, size version
 *
 * */

class DSU{
    vector<int> parents, size;
public:
    DSU(int N) {
        parents.resize(N);
        size.resize(N, 1);
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
        if (px == py) return;
        if (size[px] <= size[py]) {
            parents[px] = py;
            size[py] += size[px];
        }
        else {
            parents[py] = px;
            size[px] += size[py];
        }
    }
};

class Solution {
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        DSU dsu = DSU(m * n);
        vector<int> res;
        int cnt = 0;
        vector<vector<int>> island(m, vector<int> (n, 0));

        for (const auto& pos : positions) {
            // 如果出现重复的pos点，因为已经考虑过，所以加上之前的cnt即可
            if (island[pos[0]][pos[1]]) {
                res.push_back(cnt);
                continue;
            }

            island[pos[0]][pos[1]] = 1;
            cnt++;

            for (const auto& dir : dirs) {
                int nx = pos[0] + dir[0], ny = pos[1] + dir[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || island[nx][ny] == 0) {
                    continue;
                }

                // adjacent neighbor but not connected. use union find to join them
                int node1 = dsu.find(pos[0] * n + pos[1]);
                int node2 = dsu.find(nx * n + ny);
                if (node1 != node2) {
                    dsu.unionFunc(node1, node2);
                    cnt--;
                }
            }

            res.push_back(cnt);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
