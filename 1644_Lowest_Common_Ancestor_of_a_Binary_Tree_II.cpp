/*
solution 1 : recursion + divide and conquer
time: O(N)
space: O(N)
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
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || p == nullptr || q == nullptr)
            return nullptr;
        
        bool Pfound = search(root, p);
        bool Qfound = search(root, q);
        
        if (!Pfound || !Qfound) 
            return nullptr;
        
        return helper(root, p, q);
    }
    
private:
    TreeNode* helper(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q){
            return root;
        }
        
        TreeNode* left = helper(root->left, p, q);
        TreeNode* right = helper(root->right, p, q);
        
        if(left && right)
            return root;

        return left == nullptr ? right : left;
    }
    
    bool search(TreeNode* root, TreeNode* node) {
        if (root == nullptr) 
            return false;
        
        if (root == node) 
            return true;
        
        return search(root->left, node) || search(root->right, node);
    }    
};

/*
solution 2 : recursion + divide and conquer，解法有误，待debug
time: O(N)
space: O(N)
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
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* lca = LCA(root, p, q);
        cout << Pfound << "+" << Qfound; 
        return Pfound && Qfound ? lca : nullptr;
    }
    
private:
    bool Qfound = false;
    bool Pfound = false;
    
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) 
            return root;
        
        cout << root->val <<endl;        

        TreeNode* left = LCA(root->left, p, q);
        TreeNode* right = LCA(root->right, p, q);
        
                
        if (root = p) {
            Pfound = true;
            return root;
        }
        
        if (root = q) {
            Qfound = true;
            return root;
        }
        
//         if(left && right)
//             return root;

//         return left == nullptr ? right : left;
        
       return left == nullptr ? right : right == nullptr ? left : root;
    }
};