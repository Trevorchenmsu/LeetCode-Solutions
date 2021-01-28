/*
solution 1: DFS
time: O(mn*max(m, n))
space: O(mn)
*/
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};
        m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo_P (m, vector<int> (n, 0));
        vector<vector<int>> memo_A (m, vector<int> (n, 0));
        vector<vector<int>> res;
        
        for (int r = 0; r < m; r++) { // O(m*mn)
            dfs(matrix, memo_P, r, 0);
            dfs(matrix, memo_A, r, n - 1);
        }
        for (int c = 0; c < n; c++) { // O(n*mn)
            dfs(matrix, memo_P, 0, c);
            dfs(matrix, memo_A, m - 1, c);
        }
        for (int i = 0; i < m; i++) {  // O(mn)
            for (int j = 0; j < n; j++) {
                if (memo_P[i][j] == 1 && memo_A[i][j] == 1)
                    res.push_back({i, j});
            }
        }
        return res;
    }
    
private:
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m, n;
    void dfs(vector<vector<int>>& matrix, vector<vector<int>>& memo, int x, int y) { // O(mn)
        memo[x][y] = 1;
        for (auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || memo[nx][ny] == 1)
                continue;
            if (matrix[nx][ny] >= matrix[x][y]) {
                dfs(matrix, memo, nx, ny);
            }
        }
    }
};
/*
solution 2: BFS
time: O((m+n)*mn))
space: O(mn)
*/
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};
        m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo_P (m, vector<int> (n, 0));
        vector<vector<int>> memo_A (m, vector<int> (n, 0));
        vector<vector<int>> res;
        queue<pair<int, int>> q;
        
        // first column - O(m)
        for (int r = 0; r < m; r++) {
            q.push({r, 0});
            memo_P[r][0] = 1;
        }
        
        // first row - O(n)
        for (int c = 0; c < n; c++) {
            q.push({0, c});
            memo_P[0][c] = 1;
        }
        
        bfs(matrix, memo_P, q); // O((m+n)*mn))
        
        // last column
        for (int r = 0; r < m; r++) {
            q.push({r, n - 1});
            memo_A[r][n - 1] = 1;
        }
        
        // last row
        for (int c = 0; c < n; c++) {
            q.push({m - 1, c});
            memo_A[m - 1][c] = 1;
        }
  
        bfs(matrix, memo_A, q);
        
        for (int i = 0; i < m; i++) { 
            for (int j = 0; j < n; j++) {
                if (memo_P[i][j] == 1 && memo_A[i][j] == 1)
                    res.push_back({i, j});
            }
        }
        return res;
    }
    
private:
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m, n;
    void bfs(vector<vector<int>>& matrix, vector<vector<int>>& memo, queue<pair<int, int>>& q) {
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            for (auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];

                if (nx < 0 || nx >= m || ny < 0 || ny >= n || memo[nx][ny] == 1 )
                    continue;
                if (matrix[nx][ny] >= matrix[x][y]) {
                    q.push({nx, ny});
                    memo[nx][ny] = 1; 
                }
            }
        }
  
    }
};





