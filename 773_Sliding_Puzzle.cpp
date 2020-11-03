/*
solution 1: BFS
time:O(R∗C∗(R∗C)!), where R, C are the number of rows and columns in board. There are O((R * C)!) possible board states.
space:O(R∗C∗(R∗C)!)
*/
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int m = 2, n = 3;
        string start = "";
        string target = "123450";
        // 将 2x3 的数组转化成字符串
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                start.push_back(board[i][j] + '0');
            }
        }
        // 记录一维字符串的相邻索引
        vector<vector<int>> neighbor = {
            { 1, 3 },
            { 0, 4, 2 },
            { 1, 5 },
            { 0, 4 },
            { 3, 1, 5 },
            { 4, 2 }
        };

        /******* BFS 算法框架开始 *******/
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        int step = 0;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                string cur = q.front(); q.pop();
                // 判断是否达到目标局面
                if (target == cur) {
                    return step;
                }
                // 找到数字 0 的索引
                int idx = 0;
                for (; cur[idx] != '0'; idx++);
                // 将数字 0 和相邻的数字交换位置
                for (int adj : neighbor[idx]) {
                    string new_board = cur;
                    swap(new_board[adj], new_board[idx]);
                    // 防止走回头路
                    if (!visited.count(new_board)) {
                        q.push(new_board);
                        visited.insert(new_board);
                    }
                }
            }
            step++;
        }
        return -1;
        /******* BFS 算法框架结束 *******/
    }

};
/*
solution 2: optimized BFS
time:O(R∗C∗(R∗C)!), where R, C are the number of rows and columns in board. There are O((R * C)!) possible board states.
space:O(R∗C∗(R∗C)!)
*/


class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int row = board.size(), col = board[0].size();
        string start = "";
        string target = "123450";
        // 将数组转化成字符串
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                start.push_back(board[i][j] + '0');
            }
        }
        
        // 记录一维字符串的相邻索引
        vector<vector<int>> neighbor(row*col);
        for(int i = 0; i < neighbor.size(); i++){
            int r = i / col, c = i % col;
            if(r > 0)       neighbor[i].push_back((r - 1) * col + c);
            if(r < row - 1) neighbor[i].push_back((r + 1) * col + c);
            if(c > 0)       neighbor[i].push_back(i - 1);
            if(c < col - 1) neighbor[i].push_back(i + 1);
        }

        /******* BFS 算法框架开始 *******/
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        int step = 0;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                string cur = q.front(); q.pop();
                // 判断是否达到目标局面
                if (target == cur) {
                    return step;
                }
                // 找到数字 0 的索引
                int idx = 0;
                for (; cur[idx] != '0'; idx++);
                // 将数字 0 和相邻的数字交换位置
                for (int adj : neighbor[idx]) {
                    string new_board = cur;
                    swap(new_board[adj], new_board[idx]);
                    // 防止走回头路
                    if (!visited.count(new_board)) {
                        q.push(new_board);
                        visited.insert(new_board);
                    }
                }
            }
            step++;
        }
        return -1;
        /******* BFS 算法框架结束 *******/
    }

};


/*
solution 3: general BFS
time:O(R∗C∗(R∗C)!), where R, C are the number of rows and columns in board. There are O((R * C)!) possible board states.
space:O(R∗C∗(R∗C)!)
*/

class Solution {
public: 
    int slidingPuzzle(vector<vector<int>>& board) {
        const int m =board.size(), n = board[0].size();
        string state, goal="123450";  
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                state += (board[i][j] + '0');
                //goal += (i * n + j + 1) % (m * n) + '0'; // 12345...0
            }
        }
        
        if(goal == state) return 0;        
        queue<string> q{{state}};
        unordered_set<string> seen{state};
        
        int dirs[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
        int step = 0;
        
        while(!q.empty()){
            for(int sz = q.size(); sz-- > 0;){
                auto cur = q.front(); q.pop();                
                int i = cur.find('0');
                int r = i / n, c = i % n;     // current row, col index           
                for(int d = 0; d < 4; d++){
                    int nr = r + dirs[d][0],  nc = c + dirs[d][1]; // next row, col index
                    if(nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    string next(cur);
                    int ni = nr * n + nc;                    
                    swap(next[i], next[ni]);
                    if(seen.count(next)) continue;
                    if(goal == next) return step+1; // I'm in 'cur', 1 step away from 'next'
                    q.emplace(next);
                    seen.emplace(next);
                }
            }
            ++step;
        }
        return -1;
    }
};
