//Serialization is the process of converting a data structure or object into a s
//equence of bits so that it can be stored in a file or memory buffer, or transmit
//ted across a network connection link to be reconstructed later in the same or an
//other computer environment. 
//
// Design an algorithm to serialize and deserialize a binary tree. There is no r
//estriction on how your serialization/deserialization algorithm should work. You 
//just need to ensure that a binary tree can be serialized to a string and this st
//ring can be deserialized to the original tree structure. 
//
// Clarification: The input/output format is the same as how LeetCode serializes
// a binary tree. You do not necessarily need to follow this format, so please be 
//creative and come up with different approaches yourself. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,null,null,4,5]
//Output: [1,2,3,null,null,4,5]
// 
//
// Example 2: 
//
// 
//Input: root = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: root = [1]
//Output: [1]
// 
//
// Example 4: 
//
// 
//Input: root = [1,2]
//Output: [1,2]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 104]. 
// -1000 <= Node.val <= 1000 
// 
// Related Topics Tree Design 
// 👍 4495 👎 205


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
 * solution 1: level order traversal
 * time: O(n)
 * space: O(L), maximum length of the tree layer, serialize; O(n) for deserialize
 * */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL) {
            return "";
        }

        queue<TreeNode*> q;
        q.push(root);
        string res = "";

        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();

            if (cur == NULL) {
                res += "null,";
                continue;
            }

            res += to_string(cur->val) + ",";

            if (cur->left == NULL) {
                q.push(NULL);
            }
            else {
                q.push(cur->left);
            }

            if (cur->right == NULL) {
                q.push(NULL);
            }
            else {
                q.push(cur->right);
            }
        }

        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }

        vector<string> nodes = split(data, ',');

        int i = 0;
        TreeNode* root = new TreeNode(stoi(nodes[i]));
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();
            if (cur == NULL) {
                continue;
            }

            if (i + 1 < nodes.size() && nodes[i + 1] != "null") {
                cur->left = new TreeNode(stoi(nodes[i + 1]));
                q.push(cur->left);
            }

            if (i + 2 < nodes.size() && nodes[i + 2] != "null") {
                cur->right = new TreeNode(stoi(nodes[i + 2]));
                q.push(cur->right);
            }
            i += 2;
        }

        return root;
    }

    vector<string> split(string &s, char delimit) {
        stringstream ss(s);
        string token;
        vector<string> res;

        while (getline(ss, token, delimit)) {
            res.push_back(token);
        }

        return res;
    }
};

/*
 * solution 2: level order traversal
 * time: O(n)
 * space: O(L), maximum length of the tree layer, serialize; O(n) for deserialize
 * */

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL) {
            return "";
        }

        queue<TreeNode*> q;
        q.push(root);
        string res = "";

        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();

            if (cur == NULL) {
                res += "null,";
            }
            else {
                res += to_string(cur->val) + ",";
                q.push(cur->left);
                q.push(cur->right);
            }
        }

        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return NULL;
        }

        vector<string> nodes = split(data, ',');

        int i = 0;
        TreeNode* root = new TreeNode(stoi(nodes[i]));
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();
            if (cur == NULL) {
                continue;
            }

            if (i + 1 < nodes.size() && nodes[i + 1] != "null") {
                cur->left = new TreeNode(stoi(nodes[i + 1]));
                q.push(cur->left);
            }

            if (i + 2 < nodes.size() && nodes[i + 2] != "null") {
                cur->right = new TreeNode(stoi(nodes[i + 2]));
                q.push(cur->right);
            }
            i += 2;
        }

        return root;
    }

    vector<string> split(string &s, char delimit) {
        stringstream ss(s);
        string token;
        vector<string> res;

        while (getline(ss, token, delimit)) {
            res.push_back(token);
        }

        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
//leetcode submit region end(Prohibit modification and deletion)
