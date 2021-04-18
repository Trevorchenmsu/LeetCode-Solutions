//You are given an image that is represented by a binary matrix with 0 as a whit
//e pixel and 1 as a black pixel. 
//
// The black pixels are connected (i.e., there is only one black region). Pixels
// are connected horizontally and vertically. 
//
// Given two integers x and y that represent the location of one of the black pi
//xels, return the area of the smallest (axis-aligned) rectangle that encloses all
// black pixels. 
//
// 
// Example 1: 
//
// 
//Input: image = [["0","0","1","0"],["0","1","1","0"],["0","1","0","0"]], x = 0,
// y = 2
//Output: 6
// 
//
// Example 2: 
//
// 
//Input: image = [["1"]], x = 0, y = 0
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// m == image.length 
// n == image[i].length 
// 1 <= m, n <= 100 
// image[i][j] is either '0' or '1'. 
// 1 <= x < m 
// 1 <= y < n 
// image[x][y] == '1'. 
// The black pixels in the image only form one component. 
// 
// Related Topics Binary Search 
// 👍 246 👎 59


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(mlogn + nlogm)
 * space: O(1)
 * */
class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size(), n = image[0].size();

        int left = find_first(image, 0, y, 0); // O(mlogn)
        int right = find_last(image, y, n - 1, 0); // O(mlogn)
        int up = find_first(image, 0, x, 1); // O(nlogm)
        int down = find_last(image, x, m - 1, 1); // O(nlogm)

        return (right - left + 1) * (down - up + 1);
    }

    int find_first(vector<vector<char>>& image, int start, int end, int state) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (check(image, mid, state))
                end = mid;
            else
                start = mid;
        }

        if (check(image, start, state))
            return start;

        return end;
    }

    int find_last(vector<vector<char>>& image, int start, int end, int state) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (check(image, mid, state))
                start = mid;
            else
                end = mid;
        }

        if (check(image, end, state))
            return end;

        return start;
    }

    bool check(vector<vector<char>>& image, int idx, int state) {
        if (state == 0) { // each idx column, check each row
            for (int i = 0; i < image.size(); i++) {
                if (image[i][idx] == '1') return true;
            }
        } else { // each idx row, check each column
            for (int i = 0; i < image[0].size(); i++) {
                if (image[idx][i] == '1') return true;
            }
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
