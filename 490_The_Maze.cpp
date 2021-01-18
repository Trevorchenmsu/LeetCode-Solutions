/*
solution 1: DFS
time: O(mn)
space: O(mn)
*/
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return false;
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> visited(m, vector<int> (n));
        return dfs(maze, start, destination, visited);
    }
    
private:
    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool dfs(vector<vector<int>>& maze, vector<int> src, vector<int>& dst, vector<vector<int>>& visited) {
        if (visited[src[0]][src[1]]) return false;
        if (src[0] == dst[0] && src[1] == dst[1]) return true;
        
        visited[src[0]][src[1]] = true;
        
        for (int i = 0; i < 4; ++i) {
            int nx = src[0], ny = src[1];
            while (inMaze(nx + dir[i][0], ny + dir[i][1], maze) && 
            	   maze[nx+dir[i][0]][ny+dir[i][1]] == 0) {
                nx += dir[i][0];
                ny += dir[i][1];
            }
            
            if (dfs(maze, {nx, ny}, dst, visited)) return true;
        }
        return false;
    }
    
    bool inMaze(int x, int y, vector<vector<int>>& maze) {
        return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
    }
};

/*
solution 2: BFS
time: O(mn)
space: O(mn)
*/

class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return false;
        
        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> visited(m, vector<int> (n));
        visited[start[0]][start[1]] = true;
        queue<vector<int>> q{{start}};
        
        while (!q.empty()) {
            vector<int> src = q.front(); q.pop();
            if (src[0] == destination[0] && src[1] == destination[1]) 
                return true;
            
            for (int i = 0; i < 4; ++i) {
                int nx = src[0] + dir[i][0], ny = src[1] + dir[i][1];
                while (inMaze(nx, ny, maze) && maze[nx][ny] == 0) {
                    nx += dir[i][0];
                    ny += dir[i][1];
                }
                
                if (!visited[nx - dir[i][0]][ny - dir[i][1]]) {
                    q.push({nx - dir[i][0], ny - dir[i][1]});
                    visited[nx - dir[i][0]][ny - dir[i][1]] = true;
                }
            }
        }
        return false;
    }
    
private:
    
    bool inMaze(int x, int y, vector<vector<int>>& maze) {
        return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
    }
};