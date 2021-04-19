//Given an array nums that represents a permutation of integers from 1 to n. We 
//are going to construct a binary search tree (BST) by inserting the elements of n
//ums in order into an initially empty BST. Find the number of different ways to r
//eorder nums so that the constructed BST is identical to that formed from the ori
//ginal array nums. 
//
// For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left ch
//ild, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2
//,1] yields a different BST. 
//
// Return the number of ways to reorder nums such that the BST formed is identic
//al to the original BST formed from nums. 
//
// Since the answer may be very large, return it modulo 10^9 + 7. 
//
// 
// Example 1: 
//
// 
//
// 
//Input: nums = [2,1,3]
//Output: 1
//Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. 
//There are no other ways to reorder nums which will yield the same BST.
// 
//
// Example 2: 
//
// 
//
// 
//Input: nums = [3,4,5,1,2]
//Output: 5
//Explanation: The following 5 arrays will yield the same BST: 
//[3,1,2,4,5]
//[3,1,4,2,5]
//[3,1,4,5,2]
//[3,4,1,2,5]
//[3,4,1,5,2]
// 
//
// Example 3: 
//
// 
//
// 
//Input: nums = [1,2,3]
//Output: 0
//Explanation: There are no other orderings of nums that will yield the same BST
//.
// 
//
// Example 4: 
//
// 
//
// 
//Input: nums = [3,1,2,5,4,6]
//Output: 19
// 
//
// Example 5: 
//
// 
//Input: nums = [9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18]
//Output: 216212978
//Explanation: The number of ways to reorder nums to get the same BST is 3216212
//999. Taking this number modulo 10^9 + 7 gives 216212978.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// 1 <= nums[i] <= nums.length 
// All integers in nums are distinct. 
// 
// Related Topics Dynamic Programming 
// 👍 186 👎 27


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numOfWays(vector<int>& nums) {
        //建立原始BST
        TreeNode* root = new TreeNode(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            insertNode(root, nums[i]);
        }

        long seqNum, nodeNum;
        dfs(root, seqNum, nodeNum);

        return seqNum - 1; //减去原始BST
    }

private:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x): val(x), left(NULL), right(NULL) {}
    };

    long M = 1e9 + 7;
    vector<vector<long>> comb = vector<vector<long>> (1001, vector<long>(1001, -1));
    void dfs(TreeNode* root, long &seqNum, long &nodeNum) {
        //当root为叶子节点时，左右子节点都为空，因为序列数只有其本身一个节点（只有一种）。节点总数为1。
        if (root->left == NULL && root->right == NULL) {
            seqNum = 1;
            nodeNum = 1;
            return;
        }

        // 因为空间也算一个序列，所以初始序列个数为1，否则下面的乘积会变为0；初始节点数可以为0
        long leftSeqNum = 1, leftNodeNum = 0;
        long rightSeqNum = 1, rightNodeNum = 0;

        //我们只需要在原始的那棵树上去遍历它的左子树和右子树的序列总数和节点总数，用组合思想去计算即可
        //不用管具体的节点如何构造成不同的BST。在每次左右子树递归时，都会更新各自的序列数和节点数
        if (root->left)
            dfs(root->left, leftSeqNum, leftNodeNum);

        if (root->right)
            dfs(root->right, rightSeqNum, rightNodeNum);

        //当递归返回当前层后，左子树和右子树的4个变量已经被更新了，因此这里要更新当前根节点的序列数和节点数
        nodeNum = leftNodeNum + rightNodeNum + 1;
        seqNum = ((leftSeqNum * rightSeqNum) % M * getComb(leftNodeNum + rightNodeNum, leftNodeNum)) % M;
    }

    void insertNode(TreeNode* root, int val) {
        //每次操作插入节点构成BST，当前值与根节点进行比较，大的插入左子树，右的插入右子树
        //不满足条件的可以往下递归，插入下一层的子树
        if (val < root->val) {
            if (root->left == NULL)
                root->left = new TreeNode(val);
            else
                insertNode(root->left, val);
        }
        else {
            if (root->right == NULL)
                root->right = new TreeNode(val);
            else
                insertNode(root->right, val);
        }
    }

    //因为在递归的过程中会反复计算组合数，计算过的组合数不需要再计算，因此这里采用了记忆化搜索
    long getComb(long m, long n) {
        //已经计算过(m,n)组合
        if (comb[m][n] != -1)
            return comb[m][n];

        //边界条件
        if (n == 0) return 1;
        if (n == 1) return m;

        //因为组合的特性，如C(5,2)等于C(5,3)，所以计算较小的可以提高算力
        if (n > m - n) return getComb(m, m - n);

        //用递归法拆分组合计算
        long comb1 = getComb(m - 1, n - 1);
        long comb2 = getComb(m - 1, n);

        //其他题目中可不采用求模
        comb[m][n] = (comb1 + comb2) % M;

        return comb[m][n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
