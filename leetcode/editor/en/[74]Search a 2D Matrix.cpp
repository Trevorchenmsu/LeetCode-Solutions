//Write an efficient algorithm that searches for a value in an m x n matrix. Thi
//s matrix has the following properties: 
//
// 
// Integers in each row are sorted from left to right. 
// The first integer of each row is greater than the last integer of the previou
//s row. 
// 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
//Output: true
// 
//
// Example 2: 
//
// 
//Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
//Output: false
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 100 
// -104 <= matrix[i][j], target <= 104 
// 
// Related Topics Array Binary Search 
// 👍 3144 👎 195


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search
 * time: O(log(m*n))
 * space: O(1)
 * */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;

        int m = matrix.size(), n = matrix[0].size();

        int start = 0, end = m * n - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (matrix[mid / n][mid % n] == target)
                return true;
            else if (matrix[mid / n][mid % n] > target)
                end = mid;
            else
                start = mid;
        }

        if (matrix[start / n][start % n] == target ||
            matrix[end / n][end % n] == target)
            return true;

        return false;
    }
};


/*
 * solution 2: matrix corner
 * time: O(m + n) or O(max(m, n))
 * space: O(1)
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
//leetcode submit region end(Prohibit modification and deletion)
