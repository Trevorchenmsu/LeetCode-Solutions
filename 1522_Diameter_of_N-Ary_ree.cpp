/*
solution 1: tree height
time: O(n), we enumerate each node in the tree once and only once vice recursion
space: O(n), stack memory dut to recursion. Worst case is all the nodes are chained up in a single path.
*/

class Solution {
public:
    int diameter(Node* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
private:
    int height(Node* node, int& diameter) {
        if (node->children.size() == 0)
            return 0;
        
        // select the top two largest heights
        int maxHeight1 = 0, maxHeight2 = 0;
        for (auto child : node->children) {
            int parentHeight = height(child, diameter) + 1;
            if (parentHeight > maxHeight1) {
                maxHeight2 = maxHeight1;
                maxHeight1 = parentHeight;
            }
            else if (parentHeight > maxHeight2) {
                maxHeight2 = parentHeight;
            }
            diameter = max(diameter, maxHeight1 + maxHeight2);
        }
        return maxHeight1;
    }
};

/*
solution 2: tree depth
time: O(n), we enumerate each node in the tree once and only once vice recursion
space: O(n), stack memory dut to recursion. Worst case is all the nodes are chained up in a single path.
*/

class Solution {
public:
    int diameter(Node* root) {
        int diameter = 0;
        maxDepth(root, diameter, 0);
        return diameter;
    }
private:
    int maxDepth(Node* node, int& diameter, int currDepth) {
        if (node->children.size() == 0)
            return currDepth;
        
        // select the top two largest heights
        int maxDepth1 = currDepth, maxDepth2 = 0;
        for (auto child : node->children) {
            int depth = maxDepth(child, diameter, currDepth + 1);
            if (depth > maxDepth1) {
                maxDepth2 = maxDepth1;
                maxDepth1 = depth;
            } 
            else if (depth > maxDepth2) {
                maxDepth2 = depth;
            }
            diameter = max(diameter, maxDepth1 + maxDepth2 - 2 * currDepth);
        }
        return maxDepth1;
    }
};
           