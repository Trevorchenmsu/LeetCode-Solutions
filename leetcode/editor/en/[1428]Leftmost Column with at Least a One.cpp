//(This problem is an interactive problem.) 
//
// A row-sorted binary matrix means that all elements are 0 or 1 and each row of
// the matrix is sorted in non-decreasing order. 
//
// Given a row-sorted binary matrix binaryMatrix, return the index (0-indexed) o
//f the leftmost column with a 1 in it. If such an index does not exist, return -1
//. 
//
// You can't access the Binary Matrix directly. You may only access the matrix u
//sing a BinaryMatrix interface: 
//
// 
// BinaryMatrix.get(row, col) returns the element of the matrix at index (row, c
//ol) (0-indexed). 
// BinaryMatrix.dimensions() returns the dimensions of the matrix as a list of 2
// elements [rows, cols], which means the matrix is rows x cols. 
// 
//
// Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wr
//ong Answer. Also, any solutions that attempt to circumvent the judge will result
// in disqualification. 
//
// For custom testing purposes, the input will be the entire binary matrix mat. 
//You will not have access to the binary matrix directly. 
//
// 
// Example 1: 
//
// 
//
// 
//Input: mat = [[0,0],[1,1]]
//Output: 0
// 
//
// Example 2: 
//
// 
//
// 
//Input: mat = [[0,0],[0,1]]
//Output: 1
// 
//
// Example 3: 
//
// 
//
// 
//Input: mat = [[0,0],[0,0]]
//Output: -1 
//
// Example 4: 
//
// 
//
// 
//Input: mat = [[0,0,0,1],[0,0,1,1],[0,1,1,1]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// rows == mat.length 
// cols == mat[i].length 
// 1 <= rows, cols <= 100 
// mat[i][j] is either 0 or 1. 
// mat[i] is sorted in non-decreasing order. 
// 
// Related Topics Array Binary Search Matrix Interactive 
// 👍 802 👎 99


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */


/*
 * solution 1: binary search
 * time: O(mlogn)
 * space: O(1)
 * */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimension = binaryMatrix.dimensions();
        int rows = dimension[0], cols = dimension[1];
        int res = INT_MAX;

        for (int i = 0; i < rows; i++) {
            int idx = binarySearch(i, cols, binaryMatrix);
            if (idx != - 1) {
                res = min(res, idx);
            }
        }

        return res == INT_MAX ? -1 : res;
    }

    int binarySearch(int row, int cols, BinaryMatrix &binaryMatrix) {
        int start = 0, end = cols - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (binaryMatrix.get(row, mid) == 1) {
                end = mid;
            }
            else {
                start = mid;
            }
        }

        if (binaryMatrix.get(row, start) == 1) {
            return start;
        }

        if (binaryMatrix.get(row, end) == 1) {
            return end;
        }

        return -1;
    }
};

/*
 * Solution 2: two pointers
 * time: O(m + n)
 * space: O(1)
 * */
class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimension = binaryMatrix.dimensions();
        int m = dimension[0], n = dimension[1];
        int row = 0, col = n - 1, res = INT_MAX;
        while (row < m && col >= 0) {
            if (binaryMatrix.get(row, col) == 1) {
                res = min(res, col);
                col--;
            }
            else row++;
        }

        return res == INT_MAX ? -1 : res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
