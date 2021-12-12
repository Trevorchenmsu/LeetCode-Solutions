//You are given an m x n binary matrix grid. An island is a group of 1's (repres
//enting land) connected 4-directionally (horizontal or vertical.) You may assume 
//all four edges of the grid are surrounded by water. 
//
// An island is considered to be the same as another if and only if one island c
//an be translated (and not rotated or reflected) to equal the other. 
//
// Return the number of distinct islands. 
//
// 
// Example 1: 
//
// 
//Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: grid = [[1,1,0,1,1],[1,0,0,0,0],[0,0,0,0,1],[1,1,0,1,1]]
//Output: 3
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
// Related Topics Hash Table Depth-First Search Breadth-First Search Union Find 
//Hash Function 
// 👍 1378 👎 83


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs + set，简易版。解法一和解法二本质一样。
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        unordered_set<string> res;

        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    string path = "";
                    dfs(grid, i, j, path, "start#");
                    res.insert(path);
                }
            }
        }

        return res.size();
    }

    void dfs(vector<vector<int>>& grid, int i, int j, string &path, string dir) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0) return;
        grid[i][j] = 0;

        path += dir;
        dfs(grid, i + 1, j, path, "d");
        dfs(grid, i - 1, j, path, "u");
        dfs(grid, i, j + 1, path, "r");
        dfs(grid, i, j - 1, path, "l");
        path += "#end"; // 每个点遍历结束后加个end可以避免路径不同但是path累积相同的情况
    }
};


/*
 * solution 2: dfs + set
 * time: O(mn)
 * space: O(1)
 * */
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        unordered_set<string> res;
        vector<vector<int>> visited(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && visited[i][j] == 0) {
                    string path = "";
                    dfs(grid, visited, i, j, path, 'o');
                    res.insert(path);
                }
            }
        }

        return res.size();
    }

private:
    unordered_map<char, vector<int>> dirs = {{'u', {-1, 0}}, {'d', {1, 0}},
                                             {'r', {0, 1}}, {'l', {0, -1}}};
    int m, n;

    void dfs(vector<vector<int>>& grid, vector<vector<int>> &visited, int x0, int y0, string &path, char direction) {
        visited[x0][y0] = 1;

        path += direction;

        for (auto &[dir, coord] : dirs) {
            int x1 = x0 + coord[0], y1 = y0 + coord[1];

            if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n) {
                continue;
            }

            if (grid[x1][y1] == 0 || visited[x1][y1] == 1) {
                continue;
            }

            dfs(grid, visited, x1, y1, path, dir);
        }
        path += 'x';
    }
};

/*
 * solution 3: dfs，另一种dfs思路，用当前点与每次遍历的起始点的相对坐标存起来作为遍历路径，因为只能用有序set存vector，所以会慢点
 * time: O(mn*log(k))，k为distinct岛屿个数
 * space: O(1)
 * */
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        set<vector<vector<int>>> res;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    vector<vector<int>> island;
                    dfs(grid, island, i, j, i, j);
                    res.insert(island);
                }
            }
        }

        return res.size();
    }

private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m, n;

    void dfs(vector<vector<int>>& grid, vector<vector<int>> &island, int x0, int y0, int x, int y) {
        grid[x][y] = 0;

        for (auto &dir: dirs) {
            int x1 = x + dir[0], y1 = y + dir[1];
            if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n || grid[x1][y1] == 0) {
                continue;
            }
            island.push_back({x1 - x0, y1 - y0});
            dfs(grid, island, x0, y0, x1, y1);
        }
    }
};

/*
 * solution 4: bfs + hash
 * time: O(mn*L)， L is the length of the longest path
 * space: O(mn)
 * */


class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> visited(m, vector<int> (n, 0));
        unordered_set<string> res;

        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (grid[i][j] == 1 && visited[i][j] == 0) {
                    string path = "";
                    bfs(grid, i, j, visited, path);
                    res.insert(path);
                }
            }
        }

        return res.size();
    }

private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<string> directions = {"R", "L", "D", "U"};


    /*
     * bfs的解法比较tricky，不像dfs一路走到底，bfs逐层遍历会产生不同层走相同方向的情况，因此需要加入不同的字符来区分断层
     * */

    void bfs(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &visited, string &path) {
        queue<pair<pair<int, int>, string>> q;
        q.push({{i, j}, "o"});
        visited[i][j] = 1;

        int m = grid.size(), n = grid[0].size();


        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int x = cur.first.first, y = cur.first.second;
            string move = cur.second;
            path += move;
            path += "X";

            for (int i = 0; i < 4; i++) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];

                if (nx < 0 || nx >= m || ny < 0 || ny >= n ) {
                    continue;
                }

                if (visited[nx][ny] == 1 || grid[nx][ny] == 0) {
                    continue;
                }

                visited[nx][ny] = 1;
                q.push({{nx, ny}, directions[i]});
                path += directions[i];
                path += "O";
            }
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
