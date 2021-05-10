//Given an integer array nums, handle multiple queries of the following types: 
//
// 
// Update the value of an element in nums. 
// Calculate the sum of the elements of nums between indices left and right incl
//usive where left <= right. 
// 
//
// Implement the NumArray class: 
//
// 
// NumArray(int[] nums) Initializes the object with the integer array nums. 
// void update(int index, int val) Updates the value of nums[index] to be val. 
// int sumRange(int left, int right) Returns the sum of the elements of nums bet
//ween indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + 
//nums[right]). 
// 
//
// 
// Example 1: 
//
// 
//Input
//["NumArray", "sumRange", "update", "sumRange"]
//[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
//Output
//[null, 9, null, 8]
//
//Explanation
//NumArray numArray = new NumArray([1, 3, 5]);
//numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
//numArray.update(1, 2);   // nums = [1, 2, 5]
//numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 3 * 104 
// -100 <= nums[i] <= 100 
// 0 <= index < nums.length 
// -100 <= val <= 100 
// 0 <= left <= right < nums.length 
// At most 3 * 104 calls will be made to update and sumRange. 
// 
// Related Topics Binary Indexed Tree Segment Tree 
// 👍 1803 👎 105


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: segment tree
 * time: O(logn)
 * space: O(n)
 * */

class NumArray {
public:
    NumArray(vector<int>& nums) {
        this->nums = nums;
        root = new SegTreeNode(0, nums.size() - 1);
        buildTree(root, 0, nums.size() - 1);
    }
    
    void update(int index, int val) {
        updateSingle(root, index, val);
    }
    
    int sumRange(int left, int right) {
        return queryRange(root, left, right);
    }

private:
    class SegTreeNode {
    public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end, info;
        SegTreeNode(int a, int b): start(a), end(b), info(0), left(NULL), right(NULL) {}
    };

    void buildTree(SegTreeNode* node, int start, int end) {
        if (start == end) {
            node->info = nums[start];
            return;
        }

        int mid = (start + end) / 2;
        if (node->left == NULL) {
           node->left = new SegTreeNode(start, mid);
           node->right = new SegTreeNode(mid + 1, end);
        }

        buildTree(node->left, start, mid);
        buildTree(node->right, mid + 1, end);
        node->info = node->left->info + node->right->info;
    }

    void updateSingle(SegTreeNode* node, int idx, int val) {
        if (idx < node->start || idx > node->end)
            return;

        if (node->start == node->end) {
            node->info = val;
            return;
        }

        updateSingle(node->left, idx, val);
        updateSingle(node->right, idx, val);
        node->info = node->left->info + node->right->info;
    }

    int queryRange(SegTreeNode* node, int left, int right) {
        if (right < node->start || left > node->end)
            return 0;

        if (left <= node->start && right >= node->end)
            return node->info;

        return queryRange(node->left, left, right) + queryRange(node->right, left, right);
    }

    vector<int> nums;
    SegTreeNode* root;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
//leetcode submit region end(Prohibit modification and deletion)
