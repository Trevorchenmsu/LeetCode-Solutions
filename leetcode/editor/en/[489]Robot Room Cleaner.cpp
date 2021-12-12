//You are controlling a robot that is located somewhere in a room. The room is m
//odeled as an m x n binary grid where 0 represents a wall and 1 represents an emp
//ty slot. 
//
// The robot starts at an unknown location in the root that is guaranteed to be 
//empty, and you do not have access to the grid, but you can move the robot using 
//the given API Robot. 
//
// You are tasked to use the robot to clean the entire room (i.e., clean every e
//mpty cell in the room). The robot with the four given APIs can move forward, tur
//n left, or turn right. Each turn is 90 degrees. 
//
// When the robot tries to move into a wall cell, its bumper sensor detects the 
//obstacle, and it stays on the current cell. 
//
// Design an algorithm to clean the entire room using the following APIs: 
//
// 
//interface Robot {
//  // returns true if next cell is open and robot moves into the cell.
//  // returns false if next cell is obstacle and robot stays on the current cel
//l.
//  boolean move();
//
//  // Robot will stay on the same cell after calling turnLeft/turnRight.
//  // Each turn will be 90 degrees.
//  void turnLeft();
//  void turnRight();
//
//  // Clean the current cell.
//  void clean();
//}
// 
//
// Note that the initial direction of the robot will be facing up. You can assum
//e all four edges of the grid are all surrounded by a wall. 
//
// 
//
// Custom testing: 
//
// The input is only given to initialize the room and the robot's position inter
//nally. You must solve this problem "blindfolded". In other words, you must contr
//ol the robot using only the four mentioned APIs without knowing the room layout 
//and the initial robot's position. 
//
// 
// Example 1: 
//
// 
//Input: room = [[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,
//0,0,0,0],[1,1,1,1,1,1,1,1]], row = 1, col = 3
//Output: Robot cleaned all rooms.
//Explanation: All grids in the room are marked by either 0 or 1.
//0 means the cell is blocked, while 1 means the cell is accessible.
//The robot initially starts at the position of row=1, col=3.
//From the top left corner, its position is one row below and three columns righ
//t.
// 
//
// Example 2: 
//
// 
//Input: room = [[1]], row = 0, col = 0
//Output: Robot cleaned all rooms.
// 
//
// 
// Constraints: 
//
// 
// m == room.length 
// n == room[i].length 
// 1 <= m <= 100 
// 1 <= n <= 200 
// room[i][j] is either 0 or 1. 
// 0 <= row < m 
// 0 <= col < n 
// room[row][col] == 1 
// All the empty cells can be visited from the starting position. 
// 
// Related Topics Backtracking Interactive 
// 👍 1824 👎 109


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

/*
 * solution 1: dfs
 * time: O(V+E)
 * space: O(V)
 * */
class Solution {
public:
    void cleanRoom(Robot& robot) {
        string start = to_string(0) + "#" + to_string(0);
        unordered_set<string> visited{start};
        vector<vector<int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        dfs(robot, 0, 0, 0, visited, dirs);
    }

    void dfs(Robot& robot, int x, int y, int dir, unordered_set<string>& visited, vector<vector<int>>& dirs) {
        robot.clean();
        // 这里i的定义有trick，必须从1到4，而不是0到3，因为这个解法采用的先转右一次，是假设上面已经考虑过一个方向，所以i不能是0，
        // 否则考虑的会是dir
        for (int i = 1; i <= 4; i++) {
            // 这里是实现机器人的转向，如果没有这步操作，机器人一直指北，无法实现四个方向旋转
            // 因为在普通dfs中，我们只是根据坐标增减来判断四个方向，没有考虑运动的方向
            robot.turnRight();

            int next_dir = (dir + i) % 4;
            int nx = x + dirs[next_dir][0];
            int ny = y + dirs[next_dir][1];
            string location = to_string(nx) + "#" + to_string(ny);

            if (visited.find(location) != visited.end() || !robot.move()) {
                continue;
            }

            visited.insert(location);
            dfs(robot, nx, ny, next_dir, visited, dirs);

            // 以下操作为回溯到原始位置，先执行两次转右，将方向变为反方向，然后走回去起始点
            // 因为上述操作，方向被反向了，所以执行两次转左，把方向又改回原来的方向，下次遍历就可以基于当前这个方向进行旋转。
            robot.turnRight();
            robot.turnRight();
            robot.move();
            robot.turnLeft();
            robot.turnLeft();
        }
    }
};


/*
 * solution 2: dfs
 * time: O(V+E)
 * space: O(V)
 * */
class Solution {
public:
    void cleanRoom(Robot& robot) {
        unordered_set<string> visited;
        vector<vector<int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        dfs(robot, 0, 0, 0, visited, dirs);
    }

    void dfs(Robot& robot, int x, int y, int dir, unordered_set<string>& visited, vector<vector<int>>& dirs) {
        robot.clean();
        string loc = to_string(x) + "#" + to_string(y);
        visited.insert(loc);

        for (int i = 0; i < 4; i++) {
            int next_dir = (dir + i) % 4;
            int nx = x + dirs[next_dir][0];
            int ny = y + dirs[next_dir][1];
            string loc_new = to_string(nx) + "#" + to_string(ny);

            if (visited.find(loc_new) == visited.end() && robot.move()) {
                dfs(robot, nx, ny, next_dir, visited, dirs);
            }

            robot.turnRight();
        }

        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnLeft();
        robot.turnLeft();
    }
};
//leetcode submit region end(Prohibit modification and deletion)
