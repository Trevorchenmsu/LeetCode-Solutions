//Write an efficient algorithm that searches for a target value in an m x n inte
//ger matrix. The matrix has the following properties: 
//
// 
// Integers in each row are sorted in ascending from left to right. 
// Integers in each column are sorted in ascending from top to bottom. 
// 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[1
//8,21,23,26,30]], target = 5
//Output: true
// 
//
// Example 2: 
//
// 
//Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[1
//8,21,23,26,30]], target = 20
//Output: false
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= n, m <= 300 
// -109 <= matix[i][j] <= 109 
// All the integers in each row are sorted in ascending order. 
// All the integers in each column are sorted in ascending order. 
// -109 <= target <= 109 
// 
// Related Topics Binary Search Divide and Conquer 
// 👍 4617 👎 87


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search + iteration
 * time: O(m + n)
 * space: O(1)
 *
 * */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n - 1;
        while (i < m && j > -1) {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target)
                j--;
            else
                i++;
        }

        return false;
    }
};


/*
 * solution 2: binary search + recursion
 * time: O(m + n)
 * space: O(log(m + n))
 *
 * */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n - 1;
        return helper(matrix, target, i, j);
    }


private:
    int m, n;
    bool helper(vector<vector<int>>& matrix, int target, int i, int j) {
        if (i >= m || j <= -1)
            return false;

        if (matrix[i][j] == target)
            return true;

        if (matrix[i][j] > target)
            return helper(matrix, target, i, j - 1);

        if (matrix[i][j] < target)
            return helper(matrix, target, i + 1, j);

        return false;
    }

};



//leetcode submit region end(Prohibit modification and deletion)
