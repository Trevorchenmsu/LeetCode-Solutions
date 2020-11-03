/*
solution 1: monotonic stack
time: O(m*n*n)
space: O(n)
*/
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        /* Idea:
        1. change the problem to find maximum area of rectangle histogram;
        2. For each layer, compute the available area and the maximum area;
        3. Accumulate the height in every column as long as the cell is "1". Otherwise set the height as 0;
        4. Compute the accumulative height as we do in rectangle histogram with monotonous stack method.
        
        */
        
        // corner case
        if(matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0){
            return 0;
        }
        
        // initialization
        int row = matrix.size();
        int col = matrix[0].size();
        vector<int> heights(col + 1); // the last column is used for monotonous stack
        int res = 0;
        
        // traverse the matrix
        for(int i = 0; i < row; ++i){
            stack<int> s;
            for(int j = 0; j <= col; ++j){
                if(j < col){
                    // accumulate the heights for each row
                    if(matrix[i][j] == '1'){
                        ++heights[j];
                    } else{
                        heights[j] = 0;
                    }
                }
                
                // use monotonous stack to compute the area
                while(!s.empty() && heights[j] < heights[s.top()]){
                    int curHeight = heights[s.top()]; s.pop();
                    int leftBound = s.empty() ? -1 : s.top();
                    int width = j - 1 - leftBound;
                    res = max(res, curHeight * width);
                }
                s.push(j);
            }
        }
        return res;
        
    }
};

/*
solution 2: optimized monotonic stack
time: O(m*n)
space: O(n)
*/
class Solution {
private:
    int rectangleHistogram(vector<int>& heights){
        stack<int> s;
        int res = 0;
        
        for(int j = 0; j <= heights.size();){
            int curHeight = j == heights.size() ? 0 : heights[j];
            if(!s.empty() && curHeight < heights[s.top()]){
                int height = heights[s.top()]; s.pop();
                int leftBound = s.empty() ? -1 : s.top();
                int width = j - 1 - leftBound;
                res = max(res, height * width);
            } else{
                s.push(j++);
            }
        }
        return res;
    }
    
    
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
       
        // corner case
        if(matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0){
            return 0;
        }
        
        // initialization
        int row = matrix.size();
        int col = matrix[0].size();
        vector<int> heights(col + 1); // the last column is used for monotonous stack
        int res = 0;
        
        // traverse the matrix
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                // accumulate the heights for each row
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0; 
            }
            res = max(res, rectangleHistogram(heights));
        }
        return res;
    }
};

/*
solution 3: dp
time: O(m*n)
space: O(m*n)
*/

class Solution {
private:
    int rectangleHistogram(vector<int>& heights){
        stack<int> s;
        int res = 0;
        
        for(int j = 0; j <= heights.size();){
            int curHeight = j == heights.size() ? 0 : heights[j];
            if(!s.empty() && curHeight < heights[s.top()]){
                int height = heights[s.top()]; s.pop();
                int leftBound = s.empty() ? -1 : s.top();
                int width = j - 1 - leftBound;
                res = max(res, height * width);
            } else{
                s.push(j++);
            }
        }
        return res;
    }
    
    
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
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
                dp[i][j] = matrix[i][j] == '1' ? (i == 0 ? 1 : dp[i-1][j] + 1) : 0; 
            }
            res = max(res, rectangleHistogram(dp[i]));
        }
        
        return res;
    }
};