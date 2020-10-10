/* solution 1: DFS 

Time : O(M×N), where M is the number of rows and N is the number of columns.
Space: worst case O(M×N) in case that the grid map is filled with lands 
	   where DFS goes by M×N depth.
*/

class Solution {   
private:
    void dfs(int i, int j, vector<vector<char>>& grid) {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') {
            return;
        }
        
        grid[i][j] = '0';
        dfs(i, j - 1, grid);
        dfs(i, j + 1, grid);
        dfs(i - 1, j, grid);
        dfs(i + 1, j, grid);
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
  
        // edge case
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    dfs(i, j, grid);
                    ++res;
                }
            }
        }
        
        return res;
    }
};

/* solution 1: BFS 

Time : O(M×N), where M is the number of rows and N is the number of columns.
Space: O(min(M,N)), because in worst case where the grid is filled with lands, 
		the size of queue can grow up to min(M,N).
*/


class Solution {
    
private:
    void bfs(int i, int j, vector<vector<char>>& grid) {
       pair<int, int> current(i, j);
       queue<pair<int, int>> q;
       q.push(current);
       int direction[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};  
       
       while (!q.empty()) {
           pair<int, int> cur = q.front(); q.pop();
           for (int k = 0; k < 4; ++k) {
               pair<int, int> neighbor(cur.first + direction[k][0], cur.second + direction[k][1]);
               if (neighbor.first < 0 || neighbor.second < 0 || 
                   neighbor.first >= grid.size() || neighbor.second >= grid[0].size() || 
                   grid[neighbor.first][neighbor.second] == '0') {
                   continue;
               }
               q.push(neighbor);
               grid[neighbor.first][neighbor.second] = '0';
           }
       } 
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {

        // edge case
        if (grid.empty() || grid.size() == 0 || grid[0].empty() || grid[0].size() == 0) {
            return 0;
        }
        
        int m = grid.size(), n = grid[0].size();
        int res = 0;
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
};