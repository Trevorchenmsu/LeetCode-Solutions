//On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty squa
//re represented by 0. A move consists of choosing 0 and a 4-directionally adjacen
//t number and swapping it. 
//
// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]
//]. 
//
// Given the puzzle board board, return the least number of moves required so th
//at the state of the board is solved. If it is impossible for the state of the bo
//ard to be solved, return -1. 
//
// 
// Example 1: 
//
// 
//Input: board = [[1,2,3],[4,0,5]]
//Output: 1
//Explanation: Swap the 0 and the 5 in one move.
// 
//
// Example 2: 
//
// 
//Input: board = [[1,2,3],[5,4,0]]
//Output: -1
//Explanation: No number of moves will make the board solved.
// 
//
// Example 3: 
//
// 
//Input: board = [[4,1,2],[5,0,3]]
//Output: 5
//Explanation: 5 is the smallest number of moves that solves the board.
//An example path:
//After move 0: [[4,1,2],[5,0,3]]
//After move 1: [[4,1,2],[0,5,3]]
//After move 2: [[0,1,2],[4,5,3]]
//After move 3: [[1,0,2],[4,5,3]]
//After move 4: [[1,2,0],[4,5,3]]
//After move 5: [[1,2,3],[4,5,0]]
// 
//
// Example 4: 
//
// 
//Input: board = [[3,2,4],[1,5,0]]
//Output: 14
// 
//
// 
// Constraints: 
//
// 
// board.length == 2 
// board[i].length == 3 
// 0 <= board[i][j] <= 5 
// Each value board[i][j] is unique. 
// 
// Related Topics Array Breadth-First Search Matrix 
// 👍 1194 👎 32


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: BFS
 * time: O(mn*(mn)!)，字符串总长度为mn,此题为排列为题，所以每个方案需要时间为(mn)!，构建每个方案的时间为mn，所以总共为O(mn*(mn)!)
 * space: O(mn*(mn)!)
 * */
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        int x = 0, y = 0;
        string start = "";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 0) {
                    x = i, y = j;
                }
                start += to_string(board[i][j]);
            }
        }

        string target = "123450";
        unordered_set<string> visited{start};
        string pos = to_string(x) + to_string(y);
        queue<pair<string, string>> q{{{pos, start}}};

        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        int res = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                int cur_x = cur.first[0] - '0';
                int cur_y = cur.first[1] - '0';
                int raw_idx = 3 * cur_x + cur_y;
                string state = cur.second;

                if (state == target) {
                    return res;
                }

                for (auto &dir : dirs) {
                    int nx = cur_x + dir[0], ny = cur_y + dir[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                        continue;
                    }

                    int new_idx = 3 * nx + ny;
                    string new_state = state;
                    swap(new_state[raw_idx], new_state[new_idx]);

                    auto it = visited.find(new_state);
                    if (it != visited.end()) {
                        continue;
                    }

                    visited.insert(new_state);
                    pos = to_string(nx) + to_string(ny);
                    q.push({pos, new_state});
                }
            }
            res++;
        }

        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
