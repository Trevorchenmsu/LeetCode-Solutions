//Given a root of an N-ary tree, you need to compute the length of the diameter 
//of the tree. 
//
// The diameter of an N-ary tree is the length of the longest path between any t
//wo nodes in the tree. This path may or may not pass through the root. 
//
// (Nary-Tree input serialization is represented in their level order traversal,
// each group of children is separated by the null value.) 
//
// 
// Example 1: 
//
// 
//
// 
//Input: root = [1,null,3,2,4,null,5,6]
//Output: 3
//Explanation: Diameter is shown in red color. 
//
// Example 2: 
//
// 
//
// 
//Input: root = [1,null,2,null,3,4,null,5,null,6]
//Output: 4
// 
//
// Example 3: 
//
// 
//
// 
//Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null
//,12,null,13,null,null,14]
//Output: 7
// 
//
// 
// Constraints: 
//
// 
// The depth of the n-ary tree is less than or equal to 1000. 
// The total number of nodes is between [1, 104]. 
// 
// Related Topics Tree Depth-First Search 
// 👍 265 👎 4


//leetcode submit region begin(Prohibit modification and deletion)
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

/*
 * solution 1 dfs
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int diameter(Node* root) {
        int res = 0;
        search(root, res);
        return res;
    }

    int search(Node* root, int& res) {
        // 注意这里是在叶子节点的时候返回0，而不是空节点返回0
        // 如果是空节点返回0，在叶子节点的时候就会是1，为了计算边的个数，采用这个方式
        if (root->children.size() == 0) {
            return 0;
        }

        int first_height = 0, second_height = 0;
        for (auto node : root->children) {
            int cur_height = search(node, res) + 1;
            if (cur_height > first_height) {
                second_height = first_height;
                first_height = cur_height;
            }
            else if (cur_height > second_height) {
                second_height = cur_height;
            }
            res = max(res, first_height + second_height);
        }

        return first_height;
    }
};

/*
 * solution 2 dfs
 * time: O(n)
 * space: O(1)
 * */
class Solution {
    class Solution {
    public:
        int diameter(Node* root) {
            int res = 0;
            maxDepth(root, res, 0);
            return res;
        }

        int maxDepth(Node* root, int& res, int cur_depth) {
            if (root->children.size() == 0) {
                return cur_depth;
            }

            // 需要找出第一大深度和第二大深度
            int first_depth = cur_depth, second_depth = 0;
            for (auto node : root->children) {
                // 这里的思路跟二叉树跟半径一样，只是用了for循环遍历每个分支
                int depth = maxDepth(node, res, cur_depth + 1);
                // 下面这一步就相当于二叉树最后返回左右子树的较大深度。
                if (depth > first_depth) {
                    second_depth = first_depth;
                    first_depth = depth;
                }
                else if (depth > second_depth) {
                    second_depth = depth;
                }

                // 这里的depth是按节点个数算的，题目要求输出的是边的个数。
                // 当我们分别考虑两边子树时，会同时把根节点考虑两次，所以要减去之前的节点数
                res = max(res, first_depth + second_depth - 2 * cur_depth);
            }

            return first_depth;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)
