/*
Solution 1 : DFS
time: O(n), since we use find function to get the root iterator in inorder.
space: O(n), since we store the whole tree.
*/

class Solution {
public:
    typedef vector<int>::iterator Iter;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return DFS(inorder.begin(), inorder.end(), preorder.begin(), preorder.end());
    }
    
    TreeNode* DFS(Iter in_start, Iter in_end, Iter pre_start, Iter pre_end) {
        // when the traversal is empty
        if (in_start == in_end) {
            return NULL;
        }
        
        // the first one in preorder traversal is root 
        int rootVal = *pre_start;
        // find the root val in inorder
        Iter rootIter = find(in_start, in_end, rootVal);
        TreeNode* res = new TreeNode(rootVal);
        // build left and right nodes
        res->left = DFS(in_start, rootIter, pre_start + 1, pre_start + 1 + (rootIter - in_start));
        res->right = DFS(rootIter + 1, in_end, pre_start + 1 + (rootIter - in_start), pre_end);
        return res;
    }
};