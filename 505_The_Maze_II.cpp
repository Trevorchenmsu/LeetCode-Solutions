/*
solution 1: BFS
time: O(mn*max(m,n)), possible for each vertex, so O(mn). for each vertex, it is possible
to traserve from top to bottom, from left to right in one direction, which is O(max(m,n))
so total complexity is O(mn*max(m,n))
space: O(mn), distance matrix size
*/
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return -1;
        
        int m = maze.size(), n = maze[0].size();
        const int INF = 0x3f3f3f;
        
        queue<vector<int>> q{{start}};
        vector<vector<int>> dist(m, vector<int> (n, INF)); // O(mn)
        dist[start[0]][start[1]] = 0;
        int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!q.empty()) { // O(mn)
            vector<int> cur = q.front();
            q.pop();

            for (int j = 0; j < 4; j++) {
                int nx = cur[0] + dir[j][0];
                int ny = cur[1] + dir[j][1];
                int weight = 0;
                
                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0) { // O(max(m, n))
                    nx += dir[j][0];
                    ny += dir[j][1];
                    weight++;
                }

                if (dist[nx - dir[j][0]][ny - dir[j][1]] <= weight + dist[cur[0]][cur[1]] )
                    continue;

                q.push({nx - dir[j][0], ny - dir[j][1]});
                dist[nx - dir[j][0]][ny - dir[j][1]] = weight + dist[cur[0]][cur[1]] ;
            }
        }
        return dist[destination[0]][destination[1]] == INF ? -1 : dist[destination[0]][destination[1]];
    }
};

/*
solution 2: DFS (TLE, why?)
time: O(mn*max(m,n)), possible for each vertex, so O(mn). for each vertex, it is possible
to traserve from top to bottom, from left to right in one direction, which is O(max(m,n))
so total complexity is O(mn*max(m,n))
space: O(mn), distance matrix size
*/
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return -1;
        
        m = maze.size(), n = maze[0].size();
        const int INF = 0x3f3f3f;
        
        vector<vector<int>> dist (m, vector<int> (n, INF));
        dist[start[0]][start[1]] = 0;
        
        dfs(maze, dist, start);
        
        return dist[destination[0]][destination[1]] == INF ? -1 : dist[destination[0]][destination[1]];
    }
    
private:
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m, n;
    void dfs(vector<vector<int>>& maze, vector<vector<int>>& dist, vector<int>& src) {
        
        for (auto dir : dirs) {
            int nx = src[0] + dir[0];
            int ny = src[1] + dir[1];
            int weight = 0;
            
            while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0) {
                nx += dir[0];
                ny += dir[1];
                weight++;
            }
            
            if (dist[src[0]][src[1]] + weight >= dist[nx - dir[0]][ny - dir[1]])
                continue;
            
            dist[nx - dir[0]][ny - dir[1]] = dist[src[0]][src[1]] + weight;
            vector<int> nextNode =  {nx - dir[0], ny - dir[1]};
            dfs(maze, dist, nextNode);
        }
    }
};

/*
solution 3: Dijkstra
time: O((mn)^2)
space: O(mn)
*/

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
       if (maze.empty() || maze[0].empty()) return -1;
        
        m = maze.size(), n = maze[0].size();      
        vector<vector<int>> dist (m, vector<int> (n, INF));
        dist[start[0]][start[1]] = 0; 
        vector<vector<bool>> visited(m, vector<bool> (n));
        
        dijkstra(maze, dist, visited);
        
        return dist[destination[0]][destination[1]] == INF ? -1 : dist[destination[0]][destination[1]];
    }
    
private:
    int m, n;
    const int INF = 0x3f3f3f;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<int> closestNode(vector<vector<int>>& dist, vector<vector<bool>>& visited) {
        int mini_dist = INF;
        vector<int> res = {-1, -1};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j] && dist[i][j] < mini_dist) {
                    res = {i, j};
                    mini_dist = dist[i][j];
                }
            }
        }
        
        return res;
    }
    
    void dijkstra(vector<vector<int>>& maze, vector<vector<int>>& dist, vector<vector<bool>>& visited) {
        while (true) { // O(mn), traverse all the nodes
            // get the closest node
            vector<int> nextNode = closestNode(dist, visited); // O(mn)
            if (nextNode[0] < 0) break; // no available node
            
            visited[nextNode[0]][nextNode[1]] = true;
            
            
            for (auto dir : dirs) {
                int nx = nextNode[0] + dir[0];
                int ny = nextNode[1] + dir[1];
                int weight = 0;

                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    weight++;
                }

                if (dist[nextNode[0]][nextNode[1]] + weight >= dist[nx - dir[0]][ny - dir[1]])
                    continue;

                dist[nx - dir[0]][ny - dir[1]] = dist[nextNode[0]][nextNode[1]] + weight;
            }
        }
    }
};

/*
solution 4: Dijkstra + heap
time: O(mnlog(mn))
space: O(mn)
*/

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
       if (maze.empty() || maze[0].empty()) return -1;
        
        m = maze.size(), n = maze[0].size();      
        vector<vector<int>> dist (m, vector<int> (n, INF));
        dist[start[0]][start[1]] = 0;    
        dijkstra(maze, dist, start);
        
        return dist[destination[0]][destination[1]] == INF ? -1 : dist[destination[0]][destination[1]];
    }
    
private:
    int m, n;
    const int INF = 0x3f3f3f;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
   
    void dijkstra(vector<vector<int>>& maze, vector<vector<int>>& dist, vector<int>& start) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
        minHeap.push({0, start[0], start[1]});
                     
        while (!minHeap.empty()) {
            vector<int> nextNode = minHeap.top();
            minHeap.pop();
            if (dist[nextNode[1]][nextNode[2]] < nextNode[0])
                continue;
            
            for (auto dir : dirs) {
                int nx = nextNode[1] + dir[0];
                int ny = nextNode[2] + dir[1];
                int weight = 0;

                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0) {
                    nx += dir[0];
                    ny += dir[1];
                    weight++;
                }

                if (dist[nextNode[1]][nextNode[2]] + weight >= dist[nx - dir[0]][ny - dir[1]])
                    continue;

                dist[nx - dir[0]][ny - dir[1]] = dist[nextNode[1]][nextNode[2]] + weight;
                minHeap.push({dist[nx - dir[0]][ny - dir[1]], nx - dir[0], ny - dir[1]});
            }
        }
    }
};