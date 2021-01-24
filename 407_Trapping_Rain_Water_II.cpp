/*
solution 1: BFS + set
time: O(m*n*log(m*n)), m*n for set loop, log(m*n) for erase operation.
space: O(m*n), worst case will include all the points into the set. 
*/
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        
        // ordered set to store {height, x, y}
        set<vector<int>> Set;
        
        for (int i = 0; i < m; ++i) { // insert y boundary
            Set.insert({heightMap[i][0], i, 0});
            Set.insert({heightMap[i][n - 1], i, n - 1});
            heightMap[i][0] = -1;
            heightMap[i][n - 1] = -1;
        }
        
        for (int j = 0; j < n; ++j) { // insert x boundary
            Set.insert({heightMap[0][j], 0, j});
            Set.insert({heightMap[m - 1][j], m - 1, j});
            heightMap[0][j] = -1;
            heightMap[m - 1][j] = -1;
        }
        
        vector<vector<int>> dir = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        int res = 0;
        
        while (!Set.empty()) {
            int h = (*Set.begin())[0];
            int x = (*Set.begin())[1];
            int y = (*Set.begin())[2];
            Set.erase(Set.begin());
            
            queue<pair<int, int>> q;
            q.push({x, y});
            
            while (!q.empty()) {
                pair<int, int> cur = q.front();
                q.pop();
                
                for (int k = 0; k < 4; k++) {
                    int nx = cur.first + dir[k][0];  
                    int ny = cur.second + dir[k][1];
                    
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || heightMap[nx][ny] == -1) 
                        continue;
                    
                    if (heightMap[nx][ny] <= h) {
                        res += h - heightMap[nx][ny];
                        q.push({nx, ny});
                    }
                    else 
                    	Set.insert({heightMap[nx][ny], nx, ny});                   
                    heightMap[nx][ny] = -1;
                }
            }
        }
        return res;
    }
};

/*

solution 1: BFS + heap
time: O(m*n*log(m*n)), m*n for set loop, log(m*n) for erase operation.
space: O(m*n), worst case will include all the points into the set. 
*/

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        typedef pair<int, pair<int, int>> PIII;
        int n = heightMap.size(), m = heightMap[0].size();
        
        vector<vector<bool>> st(n, vector<bool>(m, false));
        priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
        
        for (int i = 0; i < n; i ++ )
        {
            heap.push({heightMap[i][0], {i, 0}});
            heap.push({heightMap[i][m - 1], {i, m - 1}});
            st[i][0] = st[i][m - 1] = true;
        }

        for (int j = 0; j < m; j ++ )
        {
            heap.push({heightMap[0][j], {0, j}});
            heap.push({heightMap[n - 1][j], {n - 1, j}});
            st[0][j] = st[n - 1][j] = true;
        }
        
        int res = 0;
        int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
        while (heap.size())
        {
            auto t = heap.top();
            heap.pop();
            int x = t.second.first, y = t.second.second, h = t.first;

            for (int k = 0; k < 4; k ++ )
            {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;
                    
                if (st[nx][ny])
                    continue;
                
                st[nx][ny] = true;
                if (h > heightMap[nx][ny]) 
                    res += h - heightMap[nx][ny];
                heap.push({max(heightMap[nx][ny], h), {nx, ny}});
            }
        }

        return res;
    }
};
