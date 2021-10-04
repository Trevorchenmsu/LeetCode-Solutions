//Given a string expression of numbers and operators, return all possible result
//s from computing all the different possible ways to group numbers and operators.
// You may return the answer in any order. 
//
// 
// Example 1: 
//
// 
//Input: expression = "2-1-1"
//Output: [0,2]
//Explanation:
//((2-1)-1) = 0 
//(2-(1-1)) = 2
// 
//
// Example 2: 
//
// 
//Input: expression = "2*3-4*5"
//Output: [-34,-14,-10,-10,10]
//Explanation:
//(2*(3-(4*5))) = -34 
//((2*3)-(4*5)) = -14 
//((2*(3-4))*5) = -10 
//(2*((3-4)*5)) = -10 
//(((2*3)-4)*5) = 10
// 
//
// 
// Constraints: 
//
// 
// 1 <= expression.length <= 20 
// expression consists of digits and the operator '+', '-', and '*'. 
// 
// Related Topics Divide and Conquer 
// 👍 2220 👎 119


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: divide and conquer
 * time: O(C_n)，具体为卡特兰数， Catalan number
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> res;
        vector<int> left;
        vector<int> right;

        for (int i = 0; i < expression.size(); i++) {
            char ch = expression[i];
            if (isdigit(ch)) continue;
            left = diffWaysToCompute(expression.substr(0, i));
            right = diffWaysToCompute(expression.substr(i + 1));

            for (auto &v1 : left) {
                for (auto &v2 : right) {
                    if (ch == '+') res.push_back(v1 + v2);
                    if (ch == '-') res.push_back(v1 - v2);
                    if (ch == '*') res.push_back(v1 * v2);
                }
            }
        }

        if (res.empty())
            res.push_back(stoi(expression));

        return res;
    }
};


/*
 * solution: divide and conquer, another format
 * time: O(C_n)，具体为卡特兰数
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> diffWaysToCompute(string s) {
        if (s.size() == 1 || s.size() == 2 && isdigit(s[1])) {
            int num = stoi(s);
            return {num};
        }

        vector<int> res, left_res, right_res;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (isdigit(s[i])) {
                continue;
            }

            string left = s.substr(0, i);
            string right = s.substr(i + 1);
            left_res = diffWaysToCompute(left);
            right_res = diffWaysToCompute(right);
            int val = 0;
            for (auto &num1 : left_res) {
                for (auto &num2 : right_res) {
                    if (s[i] == '-') {
                        val = num1 - num2;
                    }
                    if (s[i] == '+') {
                        val = num1 + num2;
                    }
                    if (s[i] == '*') {
                        val = num1 * num2;
                    }
                    res.push_back(val);
                }
            }

        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
