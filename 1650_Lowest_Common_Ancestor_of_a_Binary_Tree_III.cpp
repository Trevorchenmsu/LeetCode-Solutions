/*
solution: iteration
time: O(p)
space: O(p), the number of parents of p
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        if (p->parent == nullptr) return p;
        if (q->parent == nullptr) return q;
        
        unordered_set<Node*> p_parent;
        while (p != nullptr) {
            p_parent.insert(p);
            p = p->parent;
        }
        
        while (p_parent.find(q) == p_parent.end()) {
            q = q->parent;
        }
        
        return q;
    }
};
