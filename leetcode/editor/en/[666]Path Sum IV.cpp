//If the depth of a tree is smaller than 5, then this tree can be represented by
// an array of three-digit integers. For each integer in this array: 
//
// 
// The hundreds digit represents the depth d of this node where 1 <= d <= 4. 
// The tens digit represents the position p of this node in the level it belongs
// to where 1 <= p <= 8. The position is the same as that in a full binary tree. 
// The units digit represents the value v of this node where 0 <= v <= 9. 
// 
//
// Given an array of ascending three-digit integers nums representing a binary t
//ree with a depth smaller than 5, return the sum of all paths from the root towar
//ds the leaves. 
//
// It is guaranteed that the given array represents a valid connected binary tre
//e. 
//
// 
// Example 1: 
//
// 
//Input: nums = [113,215,221]
//Output: 12
//Explanation: The tree that the list represents is shown.
//The path sum is (3 + 5) + (3 + 1) = 12.
// 
//
// Example 2: 
//
// 
//Input: nums = [113,221]
//Output: 4
//Explanation: The tree that the list represents is shown. 
//The path sum is (3 + 1) = 4.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 15 
// 110 <= nums[i] <= 489 
// nums represents a valid binary tree with depth less than 5. 
// 
// Related Topics Tree 
// 👍 226 👎 310

//Input: nums = [113,221]
//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution 1: hashmap + preorder traversal
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int pathSum(vector<int>& nums) {
        unordered_map<int, int> pos2val;
        int res = 0;

        for (auto &num : nums)
            pos2val[num / 10] = num % 10;

        dfs(nums[0] / 10, pos2val, 0, res);

        return res;
    }

    // preorder traversal
    void dfs(int levelPos, unordered_map<int, int> &pos2val, int sum, int &res) {
        int level = levelPos / 10, pos = levelPos % 10;
        int left = (level + 1) * 10 + 2 * pos - 1, right = left + 1;
        sum += pos2val[levelPos];

        // reach leaf node
        if (!pos2val.count(left) && !pos2val.count(right)) {
            res += sum;
            return;
        }

        if (pos2val.count(left))
            dfs(left, pos2val,sum, res);

        if (pos2val.count(right))
            dfs(right, pos2val, sum, res);
    }
};


/*
 * solution 2: level traversal (BFS) + hashtable
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int pathSum(vector<int>& nums) {
        int res = 0;

        unordered_map<int, int> pos2val;
        for (auto &num : nums)
            pos2val[num / 10] = num % 10;

        queue<int> q;
        q.push(nums[0] / 10);

        while (!q.empty()) {
            int node = q.front(); q.pop();
            int level = node / 10, pos = node % 10;
            int left = (level + 1) * 10 + 2 * pos - 1, right = left + 1;

            if (!pos2val.count(left) && !pos2val.count(right))
                res += pos2val[node];

            if (pos2val.count(left)) {
                pos2val[left] += pos2val[node];
                q.push(left);
            }

            if (pos2val.count(right)) {
                pos2val[right] += pos2val[node];
                q.push(right);
            }
        }

        return res;
    }


};


//leetcode submit region end(Prohibit modification and deletion)
