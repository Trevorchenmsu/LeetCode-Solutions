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
        SegTreeNode *left, *right;
        int start, end, info;
        SegTreeNode (int a, int b) : start(a), end(b), info(0), left(NULL), right(NULL) {}
    };

    void buildTree(SegTreeNode* node, int start, int end) {
        //当分割到只剩下一个节点时，此时返回该节点的值，用它作为该节点的info
        if (start == end) {
            node->info = nums[start];
            return;
        }

        // 创建左右子树
        int mid = (start + end) / 2;
        if (node->left == NULL) {
            node->left = new SegTreeNode(start, mid);
            node->right = new SegTreeNode(mid + 1, end);
        }

        // 分治法建树
        buildTree(node->left, start, mid);
        buildTree(node->right, mid + 1, end);
        node->info = node->left->info + node->right->info;
    }

    void updateSingle(SegTreeNode* node, int idx, int val) {
        // 边界条件
        if (idx < node->start || idx > node->end)
            return;

        // 递归出口，递归到一个节点时
        if (node->start == node->end) {
            node->info = val;
            return;
        }

        // 左右子树查找这个目标idx
        // 为什么可以找得到idx？因为上面的边界条件一直压缩有效区间，直到为单节点时，找到的就是idx
        updateSingle(node->left, idx, val);
        updateSingle(node->right, idx, val);
        // 层层往上更新父节点info。我们不用管更新的是left还是right节点，反正它的值变更了，与它相关的每一层父节点都要更新
        node->info = node->left->info + node->right->info;
    }

    int queryRange(SegTreeNode* node, int left, int right) {
        // 边界条件：左侧条件表示left和right都在start和end的左边，无效；
        // 右侧条件表示left和right都在start和end的右边，没必须继续搜索下去。
        if (right < node->start || left > node->end)
            return 0;

        /* 为什么是这种判定条件？首先start和end并不是指根节点的start和end，而是当前节点的start和end
        当left和right能够包含整个start和end时，可以有3种情况：
        （1）start和left相等，right比end大。此时我们要的就是代表这个start和end的node的info。但是缺了右半段怎么整？递归返回后就会
        去到右侧去查找另一半的info结果。(2) left比start大，right和end相等。(3)start等于left，right等于end。同理。

        S|_____|E            S|_____|E   S|__________|E
        L|__________R   L|__________|R   L|__________|R

        */
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
