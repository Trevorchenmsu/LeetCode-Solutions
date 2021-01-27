/*
solution 1: BFS + heap, TLE
time:
space: 
*/
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
        
        m = forest.size();
        n = forest[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1)
                    minHeap.push({forest[i][j], i, j});
            }
        }
                             
        vector<int> start = {0, 0};
        int res = 0;
        while (!minHeap.empty()) {
            vector<int> tree = minHeap.top();
            minHeap.pop();
            vector<int> target = {tree[1], tree[2]};
            vector<vector<bool>> visited(m, vector<bool> (n));
            if(!bfs(forest, start, target, res, visited))
                return -1;
        }
                             
        return res;
    }

private:
    int m, n;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool bfs(vector<vector<int>>& forest, vector<int>& start, vector<int>& target, int& res,vector<vector<bool>>& visited) {
        queue<vector<int>> q;
        q.push(start);

        while (!q.empty()){
            int size = q.size();
            while (size--) {
                vector<int> cur = q.front();
                q.pop();
                if (cur[0] == target[0] && cur[1] == target[1]) {
                    start = target;
                    return true;
                }
                for (auto dir : dirs) {
                    int x = cur[0] + dir[0];
                    int y = cur[1] + dir[1];
                    if (x < 0 || x >= m || y < 0 || y >= n || forest[x][y] == 0 || visited[x][y])
                        continue;
                    q.push({x, y});
                    visited[x][y] = true;
                }
               
                forest[cur[0]][cur[1]] = 1;
            }
            res++;
        }
        return false;
    }
};


/*
solution 2: BFS + treeMap, TLE
time:
space: 
*/
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        m = forest.size();
        n = forest[0].size();
        map<int, pair<int, int>> trees;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1)
                    trees[forest[i][j]] = {i, j};
            }
        }
        
        int sx = 0, sy = 0;
        int res = 0;
        for (auto& tree : trees) {
            int tx = tree.second.first;
            int ty = tree.second.second;
            int step = bfs(forest, sx, sy, tx, ty);
            if (step == -1)
                return -1;
            else
                res += step;
            sx = tx;
            sy = ty;
        }
        
        return res;
    }

private:
    int m, n;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int bfs(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        queue<vector<int>> q;
        q.push({sx, sy});
        vector<vector<bool>> visited(m, vector<bool> (n));
        visited[sx][sy] = true;
        int step = 0;
        
        while (!q.empty()){
            int size = q.size();
            while (size--) {
                int i = q.front()[0];
                int j = q.front()[1];
                q.pop();
                
                if (i == tx && j == ty) 
                    return step;
                
                for (auto dir : dirs) {
                    int x = i + dir[0];
                    int y = j + dir[1];
                    
                    if (x < 0 || x >= m || y < 0 || y >= n)
                        continue;
                    if (forest[x][y] == 0 || visited[x][y])
                        continue;
                    
                    q.push({x, y});
                    visited[x][y] = true;
                }
            }
            step++;
        }
        return -1;
    }
};

/*
solution 3: BFS + treeMap, pass
time:
space: 
*/
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        map<int, pair<int, int>> Map;
        M = forest.size();
        N = forest[0].size();
        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (forest[i][j] > 1)
                    Map[forest[i][j]] = {i, j};
            }
        }
        
        int x = 0, y = 0;
        int res = 0;
        for (auto& a : Map) {
            int m = a.second.first;
            int n = a.second.second;
            int step = bfs(x, y, m, n, forest);
            if (step == -1) return -1;
            else res += step;
            x = m;
            y = n;
        }
        return res;
    }
private:
    int M, N;
    int bfs(int x, int y, int m, int n, vector<vector<int>>& forest) {
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<int>> visited(M, vector<int> (N, 0));
        
        if (x == m && y == n) return 0;
        queue<pair<int, int>> q;
        q.push({x, y});
        visited[x][y] = 1;
        int step = 0;
        
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                
                for (auto& dir : dirs) {
                    int i = x + dir[0];
                    int j = y + dir[1];
                    
                    if (i == m && j == n) return step + 1;
                    if (i < 0 || i >= M || j < 0 || j >= N)
                        continue;
                    if (forest[i][j] == 0 || visited[i][j] == 1)
                        continue;
                    q.push({i, j});
                    visited[i][j] = 1;
                }
            }
            step++;
        }
        return -1;
    }
};