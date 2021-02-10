/*
solution 1: bfs + ordered set
time: O(n*n*logn)
space: o(n*n)
*/
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if (x == 0 && y == 0) 
            return 0;
        
        x = abs(x), y = abs(y); // only consider first quadrant
        queue<pair<int, int>> q;
        q.push({0, 0});
        set<pair<int, int>> visited;
        visited.insert({0, 0});
        int dirs[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, 
                      {1, 2}, {2, 1}, {2, -1}, {1, -2}};
        
        int res = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                for (auto dir : dirs) {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                    if (nx == x && ny == y)
                        return res + 1;
                    pair<int, int> next = make_pair(nx, ny);
                    if (visited.count(next)) 
                    	continue;
                    // if target in (1,1), we cannot reach it from (0, 0)
                    // so we need to trace back to (-1,-1) so it can reach this condition
                   	if (abs(nx) + abs(ny) > 300 || nx < -1 || ny < -1 ) 
                   		continue;
                    q.push(next);
                    visited.insert(next);
                }
            }
            res++;
        }
        return -1;
    } 
};

/*
solution 2: bfs + optimization
time: O(n*n)
space: o(n*n)
*/
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if (x == 0 && y == 0) 
            return 0;
        
        x = abs(x), y = abs(y); // only consider first quadrant

        queue<pair<int, int>> q;
        q.push({0, 0});

        vector<vector<int>> visited(303, vector<int> (303));
        visited[2][2] = 1;

        int dirs[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, 
                      {1, 2}, {2, 1}, {2, -1}, {1, -2}};
        
        int res = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                if (i == x && j == y)
                	return res;
                for (auto dir : dirs) {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                   	if (abs(nx) + abs(ny) > 300 || nx < -1 || ny < -1 ) 
                   		continue;
                    if (visited[nx + 2][ny + 2]) 
                    	continue;
             
                    visited[nx + 2][ny + 2] = 1;
                    q.push({nx, ny});
                }
            }
            res++;
        }
        return -1;
    } 
};