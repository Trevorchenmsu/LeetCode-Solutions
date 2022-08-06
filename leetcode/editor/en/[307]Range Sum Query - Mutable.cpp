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
 * time: O(logn), update和query都是logn，logn为树高
 * space: O(n)
 * */

class SegTreeNode {
public:
    SegTreeNode *left, *right;
    int start, end, info;
    SegTreeNode(int start_, int end_): start(start_), end(end_), info(0), left(nullptr), right(nullptr) {}
};

class NumArray {
    vector<int> nums;
    SegTreeNode* root;

    void buildTree(SegTreeNode* node, int start, int end) {
        // 当分割到叶节点时，用数组上对应的值更新改叶节点对应的info
        if (start == end)
        {
            node->info = nums[start];
            return;
        }

        // 创建左右子树
        int mid = (start + end) / 2;
        if (!node->left)
        {
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
        if (idx < node->start || idx > node->end) return;

        // 递归出口，当递归到叶节点时
        if (node->start == node->end)
        {
            node->info = val;
            return;
        }

        // 左右子树查找idx的位置。因为上面的边界条件一直压缩有效区间，直到叶节点，找到的就是idx
        updateSingle(node->left, idx, val);
        updateSingle(node->right, idx, val);

        // 更新父级节点info。不用管更新的是left还是right节点，反正它的值变更了，与它相关的每一层父节点都要更新
        node->info = node->left->info + node->right->info;
    }

    int queryRange(SegTreeNode* node, int left, int right) {
        // 边界条件: 左边表示left和right都在start和end的左边，无效；
        // 右边表示left和right都在start和end的右边，无效。
        if (right < node->start || left > node->end) return 0;

        /* 首先start和end并不是指根节点的start和end，而是当前节点的start和end。
        当指定的left和right能够包含整个start和end时，可以有3种情况：
        （1）start和left相等，right比end大。此时我们要的就是代表这个start和end的node的info。
            右半段的值在递归返回后就会去右侧查找另一半的info结果。
            这个例子中相当于return的queryRange(node->left, left, right)，它结束回来后，又会去
            queryRange(node->right, left, right)查找另一半
         (2) left比start宽，right和end相等。相当于左侧已经执行完了，SE属于右侧的queryRange(node->right, left, right)
         (3) start等于left，right等于end。同理。

        S|_____|E            S|_____|E   S|__________|E
        L|__________R   L|__________|R   L|__________|R
        下面的两种情况下SE的区间和根本不能用，它超过了LR的范围，无法代表LR区间，所以不需要考虑。
        也就是说必须(left, right)和(start, end)有重叠区间才可以使用SE的值，而且还得是LR区间更大或者相等。
            S|_____|E      S|_____|E
        L|_____R               L|_____R
        */
        if (left <= node->start && right >= node->end) return node->info;

        return queryRange(node->left, left, right) + queryRange(node->right, left, right);
    }

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
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
//leetcode submit region end(Prohibit modification and deletion)
