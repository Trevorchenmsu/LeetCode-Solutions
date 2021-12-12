//In an infinite chess board with coordinates from -infinity to +infinity, you h
//ave a knight at square [0, 0]. 
//
// A knight has 8 possible moves it can make, as illustrated below. Each move is
// two squares in a cardinal direction, then one square in an orthogonal direction
//. 
//
// 
//
// Return the minimum number of steps needed to move the knight to the square [x
//, y]. It is guaranteed the answer exists. 
//
// 
// Example 1: 
//
// 
//Input: x = 2, y = 1
//Output: 1
//Explanation: [0, 0] → [2, 1]
// 
//
// Example 2: 
//
// 
//Input: x = 5, y = 5
//Output: 4
//Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
// 
//
// 
// Constraints: 
//
// 
// |x| + |y| <= 300 
// 
// Related Topics Breadth-First Search 
// 👍 798 👎 264


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs + space slack + set
 * time: O(n^2*logn)
 * space: O(n^2)
 * */
class Solution {
public:
    int minKnightMoves(int x, int y) {
        int dirs[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                          {1, 2}, {2, 1}, {2, -1}, {1, -2}};

        if (x == 0 && y == 0)
            return 0;

        x = abs(x), y = abs(y);

        queue<pair<int, int>> q;
        q.push({0, 0});

        set<pair<int, int>> visited;
        visited.insert({0, 0});

        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int cur_x = q.front().first;
                int cur_y = q.front().second;
                q.pop();

                if (cur_x == x && cur_y == y)
                    return step;

                for (auto dir : dirs) {
                    int nx = cur_x + dir[0], ny = cur_y + dir[1];

                    auto iter = visited.find({nx, ny});
                    if (iter != visited.end()) {
                        continue;
                    }

                    if (abs(nx) + abs(ny) > 300 || nx < -1 || ny < -1) {
                        continue;
                    }

                    q.push({nx, ny});
                    visited.insert({nx, ny});
                }
            }
            step++;
        }
        return -1;
    }
};

/*
 * solution 2: bfs + space slack + vector
 * time: O(n^2), slower than optimal solution because it needs to consider four quadrants
 * space: O(n^2)
 * */

class Solution {
public:
    int minKnightMoves(int x, int y) {
        vector<vector<int>> dirs{{-2, 1}, {-1, 2}, {1, 2}, {2, 1},
                                 {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

        vector<vector<int>> visit(601, vector<int>(601, 0));
        visit[300][300] = 1;

        queue<pair<int, int>> q;
        q.push({0, 0});

        int step = 0;
        while(!q.empty()){
            int len = q.size();
            while(len--){
                auto cur = q.front(); q.pop();

                if(cur.first == x && cur.second == y){
                    return step;
                }

                for(auto &dir : dirs){
                    int nx = cur.first + dir[0], ny = cur.second + dir[1];

                    if (abs(nx) + abs(ny) > 300) {
                        continue;
                    }

                    if( visit[nx + 300][ny + 300] == 1){
                        continue;
                    }

                    q.push({nx, ny});
                    visit[nx + 300][ny + 300] = 1;
                }
            }
            ++step;
        }
        return 0;
    }
};

/*
 * solution 3: bfs + space slack + vector
 * time: O(n^2), optimal, faster because it only consider first quadrant
 * space: O(n^2)
 * */

class Solution {
public:
    int minKnightMoves(int x, int y) {
        if (x == 0 && y == 0)
            return 0;

        x = abs(x), y = abs(y); // only consider first quadrant

        queue<pair<int, int>> q;
        q.push({0, 0});

        vector<vector<int>> visited(302, vector<int> (302));
        visited[1][1] = 1;

        int dirs[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                          {1, 2}, {2, 1}, {2, -1}, {1, -2}};

        int res = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int x_cur = q.front().first;
                int y_cur = q.front().second;
                q.pop();

                if (x_cur == x && y_cur == y)
                    return res;

                for (auto dir : dirs) {
                    int nx = x_cur + dir[0], ny = y_cur + dir[1];

                    if (abs(nx) + abs(ny) > 300 || nx < -1 || ny < -1 )
                        continue;

                    if (visited[nx + 1][ny + 1])
                        continue;

                    visited[nx + 1][ny + 1] = 1;
                    q.push({nx, ny});
                }
            }
            res++;
        }
        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
