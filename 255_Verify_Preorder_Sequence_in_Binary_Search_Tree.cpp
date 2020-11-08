/*
solution 1: stack
time: O(n), travese the array
space: O(n), worst case is all the nodes are left children
*/
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int low = INT_MIN;
        stack<int> s;
        for (auto a : preorder) {
            if (a < low) return false;
            while (!s.empty() && a > s.top()) {
                low = s.top(); s.pop();
            }
            s.push(a);
        }
        return true;
    }
};
/*
solution: no stack
time: O(n), travese the array
space: O(1)
*/
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int low = INT_MIN, i = -1;
        for (auto a : preorder) {
            if (a < low) return false;
            while (i >= 0 && a > preorder[i]) {
                low = preorder[i--];
            }
            preorder[++i] = a;
        }
        return true;
    }
};
