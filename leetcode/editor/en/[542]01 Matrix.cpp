//Given an m x n binary matrix mat, return the distance of the nearest 0 for eac
//h cell. 
//
// The distance between two adjacent cells is 1. 
//
// 
// Example 1: 
//
// 
//Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
//Output: [[0,0,0],[0,1,0],[0,0,0]]
// 
//
// Example 2: 
//
// 
//Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
//Output: [[0,0,0],[0,1,0],[1,2,1]]
// 
//
// 
// Constraints: 
//
// 
// m == mat.length 
// n == mat[i].length 
// 1 <= m, n <= 104 
// 1 <= m * n <= 104 
// mat[i][j] is either 0 or 1. 
// There is at least one 0 in mat. 
// 
// Related Topics Array Dynamic Programming Breadth-First Search Matrix 
// 👍 3419 👎 163


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs, TLE
 * time: O(mn*mn)
 * space: O(mn)
 * */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].size() == 0) {
            return {};
        }

        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> res(m, vector<int> (n));

        /*
         * 为什么普通的bfs从1进行验证会超时？因为对于每个1而言，查找的是0，当我们置为0为距离时，在这个路径上只会
         * 设置一次。如果从0开始查找，则会对所有的1都进行设置，因此减少了查找范围。当前解法从时间复杂度来看也可以
         * 知道它跟暴力解四个循环没啥区别。
         * */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    continue;
                }
                vector<vector<int>> visited(m, vector<int> (n));
                bfs(i, j, mat, visited, res);
            }
        }

        return res;
    }

    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    void bfs(int i, int j, vector<vector<int>>& mat, vector<vector<int>>& visited,  vector<vector<int>>& res) {
        queue<pair<int, int>> q{{{i, j}}};
        visited[i][j] = 1;

        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                int x = cur.first, y = cur.second;
                if (mat[x][y] == 0) {
                    res[i][j] = step;
                    return;
                }

                for (auto &dir : dirs) {
                    int nx = x + dir[0], ny = y + dir[1];

                    if (nx < 0 || nx >= mat.size() || ny < 0 || ny >= mat[0].size()) {
                        continue;
                    }

                    if (visited[nx][ny] == 1) {
                        continue;
                    }

                    q.push({nx, ny});
                    visited[nx][ny] = 1;
                }
            }

            step++;
        }
    }
};

/*
 * solution 2: bfs, optimized
 * time: O(mn)
 * space: O(1)
 * */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].size() == 0) {
            return {};
        }

        int m = mat.size(), n = mat[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                }
                else {
                    mat[i][j] = INT_MAX;
                }
            }
        }

        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int x = cur.first, y = cur.second;
            for (auto &dir : dirs) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                // 关键点就在这一步。这里类似dijkstra的dist矩阵定义，初始化为无穷大，如果遇到更小的
                // 距离就对其更新。因为当前的(x,y)已经更新，所以用它来检测邻居，满足要求就用较小值更新
                if (mat[nx][ny] < mat[x][y] + 1) {
                    continue;
                }
                mat[nx][ny] = mat[x][y] + 1;
                q.push({nx, ny});
            }
        }

        return mat;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
