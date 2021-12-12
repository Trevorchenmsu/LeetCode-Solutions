//Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be v
//alidated according to the following rules: 
//
// 
// Each row must contain the digits 1-9 without repetition. 
// Each column must contain the digits 1-9 without repetition. 
// Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 with
//out repetition. 
// 
//
// Note: 
//
// 
// A Sudoku board (partially filled) could be valid but is not necessarily solva
//ble. 
// Only the filled cells need to be validated according to the mentioned rules. 
//
// 
//
// 
// Example 1: 
//
// 
//Input: board = 
//[["5","3",".",".","7",".",".",".","."]
//,["6",".",".","1","9","5",".",".","."]
//,[".","9","8",".",".",".",".","6","."]
//,["8",".",".",".","6",".",".",".","3"]
//,["4",".",".","8",".","3",".",".","1"]
//,["7",".",".",".","2",".",".",".","6"]
//,[".","6",".",".",".",".","2","8","."]
//,[".",".",".","4","1","9",".",".","5"]
//,[".",".",".",".","8",".",".","7","9"]]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: board = 
//[["8","3",".",".","7",".",".",".","."]
//,["6",".",".","1","9","5",".",".","."]
//,[".","9","8",".",".",".",".","6","."]
//,["8",".",".",".","6",".",".",".","3"]
//,["4",".",".","8",".","3",".",".","1"]
//,["7",".",".",".","2",".",".",".","6"]
//,[".","6",".",".",".",".","2","8","."]
//,[".",".",".","4","1","9",".",".","5"]
//,[".",".",".",".","8",".",".","7","9"]]
//Output: false
//Explanation: Same as Example 1, except with the 5 in the top left corner being
// modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is inval
//id.
// 
//
// 
// Constraints: 
//
// 
// board.length == 9 
// board[i].length == 9 
// board[i][j] is a digit 1-9 or '.'. 
// 
// Related Topics Array Hash Table Matrix 
// 👍 3583 👎 623


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: brute force
 * time: O(1)
 * space: O(1)
 * */
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int> (9));
        vector<vector<int>> col(9, vector<int> (9));
        vector<vector<int>> box(9, vector<int> (9));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }

                int num = board[i][j] - '1';
                /*
                box坐标计算：把整个矩阵看成是9个box，所以有角标0-8，box的第一维即为这个box的角标，我们根据i和j的具体
                情况，将其转化为box角标，如i=2，j=2属于第一个box的右下角元素，2/3+2/3 * 3=0，即第一个box角标为0；
                又例如i=8，j=8，表示第九个box，最右下角的位置，8/3+8/3*3=2+6=8，即第九个box角标为8。通过两个例子分析
                可以知道j/3+(i/3)*3计算出来的结果就是box角标。那么box第二维表示什么？可以看到box第二维长度维9，实际上
                就是把box拉平成一个长度为9的向量，不用具体管box里面元素的位置，只要box出现一个数字，例如9，角标为8的位置
                就会赋予1。当box里面其它位置的元素也为9时，就会发现已经赋值过，所以可以确定出现重复元素，返回false。
                */
                if (row[i][num] || col[num][j] || box[j/3 + (i/3)*3][num]) {
                    return false;
                }
                row[i][num] = 1;
                col[num][j] = 1;
                box[j/3 + (i/3)*3][num] = 1;
            }
        }

        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
