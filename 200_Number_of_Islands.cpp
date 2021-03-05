/* solution 1: DFS 

Time : O(V+E) = O(M×N), where M is the number of rows and N is the number of columns.
Space: worst case O(M×N) in case that the grid map is filled with lands 
	   where DFS goes by M×N depth.
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) 
            return 0;
        
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    res++;
                }
            }
        }
        
        return res;
    }
    
private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0')
            return;
        
        grid[i][j] = '0';
        for (const auto& dir : dirs) {
            int x = i + dir[0], y = j + dir[1];
            dfs(grid, x, y);
        }
    }
};

/* solution 2: BFS + modify grid

Time : O(M×N), where M is the number of rows and N is the number of columns.
Space: O(min(M,N)), because in worst case where the grid is filled with lands, 
		the size of queue can grow up to min(M,N).
*/


class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        // edge case
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return res;
        }
        int m = grid.size(), n = grid[0].size();
        // BFS solution
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    bfs(i, j, grid);
                    ++res;
                }
            }
        }
        return res;
    }
    
private:
    void bfs(int i, int j, vector<vector<char>>& grid) {
        pair<int, int> current(i, j); 
        int direction[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        queue<pair<int, int>> Q;
        Q.push(current);
        
        while (!Q.empty()) {
            pair<int, int> cur = Q.front();
            Q.pop();
            for (int k = 0; k < 4; ++k) {
                pair<int, int> neighbor(cur.first + direction[k][0], cur.second + direction[k][1]);
                int nx = neighbor.first;
                int ny = neighbor.second;
                if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size() || grid[nx][ny] == '0') {
                    continue;
                }
                Q.push(neighbor);
                grid[nx][ny] = '0';
                
            }
        }
    }
    
};

/* solution 3: BFS + memo

Time : O(M×N), where M is the number of rows and N is the number of columns.
Space: O(min(M,N)), because in worst case where the grid is filled with lands, 
    the size of queue can grow up to min(M,N).
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) 
            return 0;
        
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<int>> visited(m, vector<int> (n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '0' || visited[i][j]) continue;
                bfs(grid, i, j, visited);
                res++;
            }
        }
        
        return res;
    }
    
private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    void bfs(vector<vector<char>>& grid, int i, int j,  vector<vector<int>>&  visited) {
        pair<int, int> start(i, j);
        queue<pair<int, int>> q;
        q.push(start);
        visited[i][j] = 1;
        
        while (!q.empty()) {
            pair<int, int> node = q.front();
            q.pop();
            for (const auto& dir : dirs) {
                int x = node.first + dir[0];
                int y = node.second + dir[1];
                
                if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() )
                    continue;
                if (visited[x][y] || grid[x][y] == '0')
                    continue;
                
                pair<int, int> new_node(x, y);
                q.push(new_node);
                visited[x][y] = 1;
            }
        }
    }
};