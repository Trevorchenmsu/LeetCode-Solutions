//One way to serialize a binary tree is to use preorder traversal. When we encou
//nter a non-null node, we record the node's value. If it is a null node, we recor
//d using a sentinel value such as '#'. 
//
// For example, the above binary tree can be serialized to the string "9,3,4,#,#
//,1,#,#,2,#,6,#,#", where '#' represents a null node. 
//
// Given a string of comma-separated values preorder, return true if it is a cor
//rect preorder traversal serialization of a binary tree. 
//
// It is guaranteed that each comma-separated value in the string must be either
// an integer or a character '#' representing null pointer. 
//
// You may assume that the input format is always valid. 
//
// 
// For example, it could never contain two consecutive commas, such as "1,,3". 
// 
//
// 
// Example 1: 
// Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
//Output: true
// Example 2: 
// Input: preorder = "1,#"
//Output: false
// Example 3: 
// Input: preorder = "9,#,#,1"
//Output: false
// 
// 
// Constraints: 
//
// 
// 1 <= preorder.length <= 104 
// preoder consist of integers in the range [0, 100] and '#' separated by commas
// ','. 
// 
//
// 
// Follow up: Find an algorithm without reconstructing the tree. 
// Related Topics Stack 
// 👍 942 👎 57


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: stack idea
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int slot = 1;
        vector<string> nodes = split(preorder, ',');

        for (auto &node : nodes) {
            slot--;
            if (slot < 0) return false;
            if (node != "#") slot += 2;
        }

        return slot == 0;
    }


private:
    vector<string> split(string &s, char delimit) {
        vector<string> res;
        stringstream ss(s);
        string token;

        while (getline(ss, token, delimit)) {
            res.push_back(token);
        }

        return res;
    }
};


/*
 * solution: dfs
 * time: O(n)
 * space: O(logn)
 * */
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int pos = 0;
        return dfs(preorder, pos) && pos >= preorder.length();
    }

    bool dfs(string &s, int &pos) {
        if (pos >= s.length()) return false;
        if (s[pos] == '#') {
            pos += 2;
            return true;
        }

        while (pos < s.length() && isdigit(s[pos]))
            pos++;

        pos++;

        return dfs(s, pos) && dfs(s, pos);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
