//You are given a 0-indexed binary string s and two integers minJump and maxJump
//. In the beginning, you are standing at index 0, which is equal to '0'. You can 
//move from index i to index j if the following conditions are fulfilled: 
//
// 
// i + minJump <= j <= min(i + maxJump, s.length - 1), and 
// s[j] == '0'. 
// 
//
// Return true if you can reach index s.length - 1 in s, or false otherwise. 
//
// 
// Example 1: 
//
// 
//Input: s = "011010", minJump = 2, maxJump = 3
//Output: true
//Explanation:
//In the first step, move from index 0 to index 3. 
//In the second step, move from index 3 to index 5.
// 
//
// Example 2: 
//
// 
//Input: s = "01101110", minJump = 2, maxJump = 3
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 2 <= s.length <= 105 
// s[i] is either '0' or '1'. 
// s[0] == '0' 
// 1 <= minJump <= maxJump < s.length 
// 
// Related Topics Two Pointers String Prefix Sum 
// 👍 653 👎 39


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: monotonic stack
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        queue<int> q({0});

        for (int i = 0; i < n && i != string::npos; i = s.find_first_of("0", i + 1)) {
            // 除了第一个i=0，剩下的i都是通过查找得到的"0"位置，所以可以确保一定为‘0’字符
            // 如果新角标不满足要求，表示超出滑窗边界，滑窗右移，删掉左边出框的边界。
            while (!q.empty() && i - maxJump > q.front()) q.pop();

            // 如果满足以下要求，表明当前i在滑窗内，所以加入队列中。如果为n-1，则可跳到终点。
            if (!q.empty() && i - minJump >= q.front()) {
                q.push(i);
                if (i == n - 1) return true;
            }

            // 如果队列是空的，表示没有可以接续跳的位置，即无法抵达，返回false
            if (q.empty()) return false;
        }

        return false;
    }
};

/*
 * solution 2: monotonic stack
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        queue<int> q({0});

        vector<int> zero_idx;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '0') zero_idx.push_back(i);
        }


        int i = 0;
        while (!zero_idx.empty()) {
            i = zero_idx.back();
            zero_idx.pop_back();
            while (!q.empty() && i - maxJump > q.front()) q.pop();
            if (!q.empty() && i - minJump >= q.front()) {
                q.push(i);
                if (i == n - 1) return true;
            }
            if (q.empty()) return false;
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
