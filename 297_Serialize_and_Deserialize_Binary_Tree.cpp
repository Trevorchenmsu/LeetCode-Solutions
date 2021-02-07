/*
solution: BFS
time:O(n)
space: O(n)
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        if (root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            auto cur = q.front(); 
            q.pop();
            if (cur == nullptr) 
                res += "nullptr,";
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
        TreeNode* root;
        if (data.empty()) return nullptr;
        vector<string> tree = split(data);
        queue<TreeNode*> q;         
        int i = 0;
        root = new TreeNode(stoi(tree[i]));;
        q.push(root);
        
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (cur != nullptr) {
                if (i + 1 < tree.size() && tree[i + 1] != "nullptr") {
                    TreeNode* left = new TreeNode(stoi(tree[i + 1]));
                    q.push(left);
                    cur->left = left;
                }
                if (i + 2 < tree.size() && tree[i + 2] != "nullptr") {
                    TreeNode* right = new TreeNode(stoi(tree[i + 2]));
                    q.push(right);
                    cur->right = right;
                }
                i += 2;
            }
        }
        return root;
    }
    
     
private:
    vector<string> split(string data, char delim = ',') {
        vector<string> res;
        stringstream ss(data);
        string token;
        while (getline(ss, token, delim)) {
            if (token != "\0") {
                res.push_back(token);
            }
        }
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
