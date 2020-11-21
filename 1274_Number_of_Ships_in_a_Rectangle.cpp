/*
solution: divide and conquer
time: O(n) where n is total number of points inside the rectangle
T(n) = 4 x T(n/4) + O(1)
Apply master theorem: n^(log(4)4) = n. So T(n) = O(n)
space: O(1)
*/


class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        if (bottomLeft[0] > topRight[0] || bottomLeft[1] > topRight[1] || !sea.hasShips(topRight, bottomLeft))
            return 0;
        
        if (bottomLeft[0] == topRight[0] && bottomLeft[1] == topRight[1])
            return 1;
        
        int new_x = (bottomLeft[0] + topRight[0]) / 2, new_y = (bottomLeft[1] + topRight[1]) / 2;
        
        return countShips(sea, {new_x, new_y}, bottomLeft) + 
               countShips(sea, topRight, {new_x + 1, new_y + 1}) + 
               countShips(sea, {new_x, topRight[1]}, {bottomLeft[0], new_y + 1}) + 
               countShips(sea, {topRight[0], new_y}, {new_x + 1, bottomLeft[1]});
    }
};