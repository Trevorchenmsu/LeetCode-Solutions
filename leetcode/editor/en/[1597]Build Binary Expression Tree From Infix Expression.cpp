//A binary expression tree is a kind of binary tree used to represent arithmetic
// expressions. Each node of a binary expression tree has either zero or two child
//ren. Leaf nodes (nodes with 0 children) correspond to operands (numbers), and in
//ternal nodes (nodes with 2 children) correspond to the operators '+' (addition),
// '-' (subtraction), '*' (multiplication), and '/' (division). 
//
// For each internal node with operator o, the infix expression that it represen
//ts is (A o B), where A is the expression the left subtree represents and B is th
//e expression the right subtree represents. 
//
// You are given a string s, an infix expression containing operands, the operat
//ors described above, and parentheses '(' and ')'. 
//
// Return any valid binary expression tree, which its in-order traversal reprodu
//ces s after omitting the parenthesis from it (see examples below). 
//
// Please note that order of operations applies in s. That is, expressions in pa
//rentheses are evaluated first, and multiplication and division happen before add
//ition and subtraction. 
//
// Operands must also appear in the same order in both s and the in-order traver
//sal of the tree. 
//
// 
// Example 1: 
//
// 
//Input: s = "3*4-2*5"
//Output: [-,*,*,3,4,2,5]
//Explanation: The tree above is the only valid tree whose inorder traversal pro
//duces s.
// 
//
// Example 2: 
//
// 
//Input: s = "2-3/(5*2)+1"
//Output: [+,-,1,2,/,null,null,null,null,3,*,null,null,5,2]
//Explanation: The inorder traversal of the tree above is 2-3/5*2+1 which is the
// same as s without the parenthesis. The tree also produces the correct result an
//d its operands are in the same order as they appear in s.
//The tree below is also a valid binary expression tree with the same inorder tr
//aversal as s, but it not a valid answer because it does not evaluate to the same
// value.
//
//The third tree below is also not valid. Although it produces the same result a
//nd is equivalent to the above trees, its inorder traversal does not produce s an
//d its operands are not in the same order as s.
//
// 
//
// Example 3: 
//
// 
//Input: s = "1+2+3+4+5"
//Output: [+,+,5,+,4,null,null,+,3,null,null,1,2]
//Explanation: The tree [+,+,5,+,+,null,null,1,2,3,4] is also one of many other 
//valid trees.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// s consists of digits and the characters '+', '-', '*', and '/'. 
// Operands in s are exactly 1 digit. 
// It is guaranteed that s is a valid expression. 
// 
// Related Topics String Tree 
// 👍 81 👎 16


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    Node* expTree(string s) {
        Node* root;
        if (s.size() == 1) {
            root = new Node(s[0]);
            return root;
        }

        // search from the end
        for (int i = s.size() - 1; i >= 0; i--) {
            // search for addition and subtraction first to find the root
            if (s[i] == '+' || s[i] == '-') {
                Node* root = new Node(s[i]);
                root->right = expTree(s.substr(i + 1));
                root->left = expTree(s.substr(0, i));
                return root;
            }
            // parenthesis matching, find the range inside parenthesis
            else if (s[i] == ')') {
                int j = i - 1;
                int count = 1;
                while (j >= 0 && count > 0) {
                    if (s[j] == ')') count++;
                    else if (s[j] == '(') count--;
                    j--;
                }
                i = j + 1;
            }
        }

        // search from the end
        for (int i = s.size() - 1; i >= 0; i--) {
            // search for multiplication and division first to find the root
            if (s[i] == '*' || s[i] == '/') {
                Node* root = new Node(s[i]);
                root->right = expTree(s.substr(i + 1));
                root->left = expTree(s.substr(0, i));
                return root;
            }
                // parenthesis matching, find the range inside parenthesis
            else if (s[i] == ')') {
                int j = i - 1;
                int count = 1;
                while (j >= 0 && count > 0) {
                    if (s[j] == ')') count++;
                    else if (s[j] == '(') count--;
                    j--;
                }
                i = j + 1;
            }
        }

        if (s[0] == '(' && s.back() == ')')
            return expTree(s.substr(1, s.size() - 2));

        return NULL;
    }


};
//leetcode submit region end(Prohibit modification and deletion)
