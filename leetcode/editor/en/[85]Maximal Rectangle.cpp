//Given a rows x cols binary matrix filled with 0's and 1's, find the largest re
//ctangle containing only 1's and return its area. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1",
//"1"],["1","0","0","1","0"]]
//Output: 6
//Explanation: The maximal rectangle is shown in the above picture.
// 
//
// Example 2: 
//
// 
//Input: matrix = []
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: matrix = [["0"]]
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: matrix = [["1"]]
//Output: 1
// 
//
// Example 5: 
//
// 
//Input: matrix = [["0","0"]]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// rows == matrix.length 
// cols == matrix[i].length 
// 0 <= row, cols <= 200 
// matrix[i][j] is '0' or '1'. 
// 
// Related Topics Array Dynamic Programming Stack Matrix Monotonic Stack 
// 👍 5101 👎 93


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: monotonic stack
 * time: O(mn)
 * space: O(n)
 * */

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        int res = 0;
        vector<int> heights(col + 1);
        for (int i = 0; i < row; ++i)
        {
            stack<int> st; // 注意：因为处理的是每一行，都需要用新栈
            for (int j = 0; j <= col; ++j)
            {
                if (j < col)
                {
                    if (matrix[i][j] == '1')
                        ++heights[j];
                    else
                        heights[j] = 0;
                }

                /*
                单调递增栈，遇到递减情况时就要开始处理。为什么单调栈能够保证考虑了连续row方向的元素？
                1. 因为采用单调递增栈，只要满足条件，元素会一直压栈，从而元素都是连续的。极限情况下所有元素
                都是递增的，全部都被压栈，结果循环结束跳出，但没有进行面积计算处理。所以定义高度数组的时候特定
                设定了长度为col+1，最后一个元素为负数，这样即使全部原始元素递增，也会因为遇到最后一个额外的负数而
                进行弹栈计算最大矩形面积。
                2. 当出现递减情况则开始弹栈处理面积。注意：当前j的高度不参与运算，只是算栈元素的有效面积。第一个弹
                栈元素为当前高度，剩下的栈顶元素则为左边界，也有可能此时栈为空，所以用-1替代，这样一减去-1，宽度就
                至少为1。
                3. 当计算完一个宽度单位后，如果后面的栈顶仍然大于j的高度，则继续弹栈处理，因为左边界的移动，宽度会
                逐渐增大。从这也可以看出，由于一直弹栈，所以考虑宽度时也都是连续的。
                */
                while (!st.empty() && heights[j] < heights[st.top()])
                {
                    int cur_height = heights[st.top()]; st.pop();
                    int left_bound = st.empty() ? -1 : st.top();
                    int width = j - 1 - left_bound;
                    int area = cur_height * width;
                    res = max(res, area);
                }
                st.push(j);
            }
        }

        return res;
    }
};
class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        row, col = len(matrix), len(matrix[0])
        res = 0
        heights = [0] * (col + 1)

        for i in range(row):
            stack = []
            for j in range(col + 1):
                if j < col:
                    heights[j] = heights[j] + 1 if matrix[i][j] == '1' else 0
                while len(stack) != 0 and heights[j] < heights[stack[-1]]:
                    cur_height = heights[stack[-1]]
                    stack.pop()
                    left_bound = -1 if len(stack) == 0 else stack[-1]
                    width = j - 1 - left_bound
                    area = cur_height * width
                    res = max(res, area)
                stack.append(j)

        return res
/*
 * solution 2: monotonic stack
 * time: O(mn)
 * space: O(n)
 * */
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        int res = 0;
        vector<int> heights(col + 1);

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }

            res = max(res, rectangleHistogram(heights));
        }

        return res;
    }

    int rectangleHistogram(vector<int> &heights)
    {
        stack<int> st;
        int res = 0;

        for (int i = 0; i <= heights.size(); )
        {
            int cur_height = i == heights.size() ? 0 : heights[i];
            if (!st.empty() && cur_height < heights[st.top()])
            {
                int height = heights[st.top()]; st.pop();
                int left_bound = st.empty() ? -1 : st.top();
                int width = i - 1 - left_bound;
                int area = height * width;
                res = max(res, area);
            }
            else st.push(i++);
        }
        return res;
    }
};

class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        def rectangleHistogram(heights):
            stack = []
            res = i = 0

            while (i <= len(heights)):
                cur_height = 0 if i == len(heights) else heights[i]
                if len(stack) != 0 and cur_height < heights[stack[-1]]:
                    height = heights[stack[-1]]
                    stack.pop()
                    left_bound = -1 if len(stack) == 0 else stack[-1]
                    width = i - 1 - left_bound
                    area = width * height
                    res = max(res, area)
                else:
                    stack.append(i)
                    i += 1

            return res

        row, col, res = len(matrix), len(matrix[0]), 0
        heights = [0] * (col + 1)

        for i in range(row):
            for j in range(col):
                heights[j] = heights[j] + 1 if matrix[i][j] == '1' else 0
            res = max(res, rectangleHistogram(heights))

    return res

/*
 * solution 3: dp + monotonic stack
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int rectangleHistogram(vector<int>& heights){
        stack<int> s;
        int res = 0;

        for(int j = 0; j <= heights.size();){
            int curHeight = j == heights.size() ? 0 : heights[j];
            if(!s.empty() && curHeight < heights[s.top()]){
                int height = heights[s.top()]; s.pop();
                int leftBound = s.empty() ? -1 : s.top();
                int width = j - 1 - leftBound;
                if (height == width) {
                    res = max(res, height * width);
                }
            } else{
                s.push(j++);
            }
        }
        return sqrt(res);
    }

    int maximalRectangle(vector<vector<int>>& matrix) {
        // corner case
        if(matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0){
            return 0;
        }

        // initialization
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int> (col + 1));
        int res = 0;

        // traverse the matrix
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if (matrix[i][j] == 1) {
                    dp[i][j] = i == 0 ? 1 : dp[i - 1][j] + 1
                }
                else {
                    dp[i][j] = 0;
                }
            }
            res = max(res, rectangleHistogram(dp[i]));
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
