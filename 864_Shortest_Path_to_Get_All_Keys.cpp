/*
solution: BFS + bitmask
time:O(mn*2^6)
space:O(mn)
*/

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        queue<vector<int>> q; // x, y, state
        vector<vector<unordered_set<int>>> visited (m, vector<unordered_set<int>> (n)); // the visited states in position(x,y)
        
        int cnt = 0;
        int finalState = 0;
        int step = -1;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    q.push({i, j, 0});
                    visited[i][j].insert(0);
                }
                // the number of keys
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
                    cnt++;
            }
        }
        
        for (int i = 0; i < cnt; i++) {
            finalState |= (1 << i);
        }
        
        while (!q.empty()) {
            step++;
            int len = q.size();
            while (len--) {
                int x = q.front()[0];
                int y = q.front()[1];
                int state = q.front()[2];
                q.pop();
                
                for (auto& dir : dirs) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    int newState = state;
                    
                    // boudardy
                    if (nx < 0 || nx >= m || ny <0 || ny >= n)
                        continue;
                    // wall
                    if (grid[nx][ny] == '#')
                        continue;
                    // encounter the lock but current state haven't changed
                    if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'F' && ((state >> (grid[nx][ny] - 'A')) & 1) == 0)
                        continue;
                    // pick the key
                    if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f')
                        newState |= (1 << (grid[nx][ny] - 'a'));
                    // visit again but the state doesn't change
                    if (visited[nx][ny].find(newState) != visited[nx][ny].end()) 
                        continue;
                    
                    // get all the key
                    if (newState == finalState)
                        return step+1;
                    
                    q.push({nx, ny, newState});
                    visited[nx][ny].insert(newState);
                    
                }
                
            }
            
        }
        
        return -1;
    }
};