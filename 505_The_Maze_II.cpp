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
solution 2: DFS
time: O(mn*max(m,n)), possible for each vertex, so O(mn). for each vertex, it is possible
to traserve from top to bottom, from left to right in one direction, which is O(max(m,n))
so total complexity is O(mn*max(m,n))
space: O(mn), distance matrix size
*/