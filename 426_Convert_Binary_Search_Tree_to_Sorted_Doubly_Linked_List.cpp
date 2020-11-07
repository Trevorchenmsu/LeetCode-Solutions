/*
solution: inorder traversial
time: O(n), traverse the tree
space: O(n), We have to keep a recursion stack of the size of the tree height, 
which is O(logN) for the best case of completely balanced tree 
and O(N) for the worst case of completely unbalanced tree.
*/

class Solution {
public:
  Node* first = NULL;
  Node* last = NULL;

  void helper(Node* node) {
      // inorder traversial
      if (!node) return;
      helper(node->left);
      if (last) {
        last->right = node;
        node->left = last;
      } else {
        first = node;
      }
      last = node;
      helper(node->right);
  }

  Node* treeToDoublyList(Node* root) {
    if (!root) return NULL;

    helper(root);
    last->right = first;
    first->left = last;
    return first;
  }
};
