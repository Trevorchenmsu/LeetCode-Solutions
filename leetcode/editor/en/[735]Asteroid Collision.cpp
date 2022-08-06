//We are given an array asteroids of integers representing asteroids in a row. 
//
// For each asteroid, the absolute value represents its size, and the sign repre
//sents its direction (positive meaning right, negative meaning left). Each astero
//id moves at the same speed. 
//
// Find out the state of the asteroids after all collisions. If two asteroids me
//et, the smaller one will explode. If both are the same size, both will explode. 
//Two asteroids moving in the same direction will never meet. 
//
// 
// Example 1: 
//
// 
//Input: asteroids = [5,10,-5]
//Output: [5,10]
//Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide
//.
// 
//
// Example 2: 
//
// 
//Input: asteroids = [8,-8]
//Output: []
//Explanation: The 8 and -8 collide exploding each other.
// 
//
// Example 3: 
//
// 
//Input: asteroids = [10,2,-5]
//Output: [10]
//Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resul
//ting in 10.
// 
//
// Example 4: 
//
// 
//Input: asteroids = [-2,-1,1,2]
//Output: [-2,-1,1,2]
//Explanation: The -2 and -1 are moving left, while the 1 and 2 are moving right
//. Asteroids moving the same direction never meet, so no asteroids will meet each
// other.
// 
//
// 
// Constraints: 
//
// 
// 2 <= asteroids.length <= 104 
// -1000 <= asteroids[i] <= 1000 
// asteroids[i] != 0 
// 
// Related Topics Array Stack 
// 👍 2596 👎 201


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> res;

        for (int i = 0; i < asteroids.size(); ++i) {
            int val = asteroids[i];
            if (val > 0) {
                res.push_back(val);
            }
            else if (res.empty() || res.back() < 0) {
                res.push_back(val);
            }
            else if (res.back() <= abs(val)) {
                //因为右边的负行星更大，所以左边的正行星消失，右边的保留位置继续考虑，用--i抵消循环中的++i，使其保持原地。
                if (res.back() < abs(val)) {
                    --i;
                }
                res.pop_back();
            }
        }

        return res;
    }
};

/*
 * solution: stack, 更加直观易懂
 * time: O(n)
 * space:O(n)
 * */
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> res;
        if (asteroids.empty() || asteroids.size() == 0)
            return res;

        stack<int> s;
        for (auto &ast : asteroids)
        {

            if(ast > 0) s.push(ast);
            else
            {
                while(!s.empty() && abs(ast) > abs(s.top()) && ast * s.top() < 0)
                    s.pop();

                if(s.empty() || s.top() < 0)
                    s.push(ast);

                else if(abs(ast) == abs(s.top()))
                    s.pop();
            }
        }

        while (!s.empty())
        {
            res.push_back(s.top()); s.pop();
        }

        reverse(res.begin(), res.end());

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
