/*
solution 1: bfs
time: O(mn*max(m, n))
space: O(mn)
*/
class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        m = maze.size(), n = maze[0].size();
        vector<vector<int>> dist(m, vector<int> (n, INF));
        dist[ball[0]][ball[1]] = 0;
        return bfs(maze, dist, ball, hole);
    }

private:
    int m, n;
    const int INF = 0x3f3f3f;
    unordered_map<char, pair<int, int>> dirs = {{'u', {-1, 0}}, {'d', {1, 0}}, {'l', {0, -1}}, {'r', {0, 1}}};
    string bfs(vector<vector<int>>& maze, vector<vector<int>>& dist, vector<int>& ball, vector<int>& hole) {
               
        queue<vector<int>> q;
        q.push(ball);
        unordered_map<int, string> u;
        
        while (!q.empty()) {
            int x = q.front()[0];
            int y = q.front()[1];
            q.pop();

            for (auto& dir : dirs) {
                int dx = dir.second.first, dy = dir.second.second;
                int nx = x + dx, ny = y + dy;
                char direction = dir.first;
                int weight = 0;
                string path = u[x * n + y];
                
                // Not out of boundary or move to the hole
                while ((nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0) && (nx != hole[0] && ny != hole[1])) {
                    nx += dx;
                    ny += dy;
                    weight++;
                }
                
                if (nx != hole[0] || ny != hole[1])
                    nx -= dx; ny -= dy; 
                
                cout << x<< " "<<y<<"->"<< nx<< " "<< ny<<": "<< dist[x][y] + weight<<endl;
                path += direction;
                
                if (dist[x][y] + weight < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + weight;
                    u[nx * n + ny] = path;
                    if (nx != hole[0] || ny != hole[1]) q.push({nx, ny});
                }
                else if (dist[x][y] + weight == dist[nx][ny] && u[nx * n + ny].compare(path) > 0) {
                    u[nx * n + ny] = path;
                    if (nx != hole[0] || ny != hole[1]) q.push({nx, ny});
                }
                
            }
        }
        string res = u[hole[0] * n + hole[1]];
        return res.empty() ? "impossible" : res;
    }
};


/*
solution 2: bfs
time: O(mn*max(m, n))
space: O(mn)
*/

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> dists(m, vector<int>(n, INT_MAX));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        vector<char> way{'l','u','r','d'};
        queue<pair<int, int>> q;
        unordered_map<int, string> u;
        dists[ball[0]][ball[1]] = 0;
        q.push({ball[0], ball[1]});
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int x = t.first, y = t.second, dist = dists[x][y];
                string path = u[x * n + y];
                while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0 && (x != hole[0] || y != hole[1])) {
                    x += dirs[i][0]; y += dirs[i][1]; ++dist;
                }
                if (x != hole[0] || y != hole[1]) {
                    x -= dirs[i][0]; y -= dirs[i][1]; --dist;
                }
                path.push_back(way[i]);
                if (dists[x][y] > dist) {
                    dists[x][y] = dist;
                    u[x * n + y] = path;
                    if (x != hole[0] || y != hole[1]) q.push({x, y});
                } else if (dists[x][y] == dist && u[x * n + y].compare(path) > 0) {
                    u[x * n + y] = path;
                    if (x != hole[0] || y != hole[1]) q.push({x, y});
                }
            }
        }
        string res = u[hole[0] * n + hole[1]];
        return res.empty() ? "impossible" : res;
        
    }
};