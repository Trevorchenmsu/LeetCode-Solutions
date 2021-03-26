//
//An image is represented by a 2-D array of integers, each integer representing 
//the pixel value of the image (from 0 to 65535).
// 
//Given a coordinate (sr, sc) representing the starting pixel (row and column) o
//f the flood fill, and a pixel value newColor, "flood fill" the image.
// 
//To perform a "flood fill", consider the starting pixel, plus any pixels connec
//ted 4-directionally to the starting pixel of the same color as the starting pixe
//l, plus any pixels connected 4-directionally to those pixels (also with the same
// color as the starting pixel), and so on. Replace the color of all of the aforem
//entioned pixels with the newColor.
// 
//At the end, return the modified image.
// 
// Example 1: 
// 
//Input: 
//image = [[1,1,1],[1,1,0],[1,0,1]]
//sr = 1, sc = 1, newColor = 2
//Output: [[2,2,2],[2,2,0],[2,0,1]]
//Explanation: 
//From the center of the image (with position (sr, sc) = (1, 1)), all pixels con
//nected 
//by a path of the same color as the starting pixel are colored with the new col
//or.
//Note the bottom corner is not colored 2, because it is not 4-directionally con
//nected
//to the starting pixel.
// 
// 
//
// Note:
// The length of image and image[0] will be in the range [1, 50]. 
// The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < im
//age[0].length. 
// The value of each color in image[i][j] and newColor will be an integer in [0,
// 65535]. 
// Related Topics Depth-first Search 
// 👍 1819 👎 238


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * Solution: DFS
 * time: O(V+E)
 * space: O(V)
 * */

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (image.empty() || image[0].empty())
            return {};

        dfs(image, sr, sc, newColor);
        return image;
    }

private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    void dfs(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (sr < 0 || sr >= image.size() || sc < 0 || sc >= image[0].size())
            return;

        int oldColor = image[sr][sc];
        image[sr][sc] = newColor;
        for (auto& dir : dirs) {
            int nx = sr + dir[0];
            int ny = sc + dir[1];

            if (nx < 0 || nx >= image.size() || ny < 0 || ny >= image[0].size())
                continue;

            if (image[nx][ny] == newColor)
                continue;

            if (image[nx][ny] == oldColor)
                dfs(image, nx, ny, newColor);
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
