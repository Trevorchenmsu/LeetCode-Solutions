//On an infinite plane, a robot initially stands at (0, 0) and faces north. The 
//robot can receive one of three instructions: 
//
// 
// "G": go straight 1 unit; 
// "L": turn 90 degrees to the left; 
// "R": turn 90 degrees to the right. 
// 
//
// The robot performs the instructions given in order, and repeats them forever.
// 
//
// Return true if and only if there exists a circle in the plane such that the r
//obot never leaves the circle. 
//
// 
// Example 1: 
//
// 
//Input: instructions = "GGLLGG"
//Output: true
//Explanation: The robot moves from (0,0) to (0,2), turns 180 degrees, and then 
//returns to (0,0).
//When repeating these instructions, the robot remains in the circle of radius 2
// centered at the origin. 
//
// Example 2: 
//
// 
//Input: instructions = "GG"
//Output: false
//Explanation: The robot moves north indefinitely. 
//
// Example 3: 
//
// 
//Input: instructions = "GL"
//Output: true
//Explanation: The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0
//, 0) -> ... 
//
// 
// Constraints: 
//
// 
// 1 <= instructions.length <= 100 
// instructions[i] is 'G', 'L' or, 'R'. 
// 
// Related Topics Math String Simulation 
// 👍 1467 👎 395


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: math
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    bool isRobotBounded(string instructions) {
        // directions: north-0, west-1, south-2, east-3
        int dirs[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
        int dir_cur = 0;
        int x = 0, y = 0;

        for (auto & ch : instructions) {
            if (ch == 'G') {
                x += dirs[dir_cur][0];
                y += dirs[dir_cur][1];
            }
            else if (ch == 'L') {
                dir_cur = (dir_cur + 1) % 4;
            }
            else {
                dir_cur = (dir_cur + 3) % 4;
            }
        }

        return x == 0 && y == 0 || dir_cur != 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
