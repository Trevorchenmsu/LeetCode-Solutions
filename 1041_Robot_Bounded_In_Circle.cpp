/*
solution 1: math
time: O(n)
space: O(1)
*/
class Solution {
public:
    bool isRobotBounded(string instructions) {
        // north = 0, east = 1, south = 2, west = 3
        int idx = 0;
        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // N, W, S, E
        int x = 0, y = 0;
        
        for (const auto& s : instructions) {
            if (s == 'L') {
                idx = (idx + 3) % 4;
            } 
            else if (s == 'R') {
                idx = (idx + 1) % 4;
            }
            else {
                x += dirs[idx][0];
                y += dirs[idx][1];
            }
        }
        
        return (x == 0 && y == 0) || (idx != 0);
    }
};


/*
solution 2: math
time: O(n)
space: O(1)
*/


class Solution {
public:
    bool isRobotBounded(string instructions) {
        int dir = 0, x = 0, y = 0,
		// moving N, W, S and E
		moves[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
        for(int i = 0; i < 4; i ++)
        {
            for (char c: instructions) {
                switch(c) {
                    // going forward
                    case 'G':
                        // updating the coordinates
                        x += moves[dir][0];
                        y += moves[dir][1];
                        break;
                    // turning left
                    case 'L':
                        dir = (dir + 1) % 4;
                        break;
                    // turning right
                    case 'R':
                        dir = (dir + 3) % 4;
                        break;
                }
            }
        }
        // return if it didn't move or didn't turn
		return !x && !y;
        
    }
};

