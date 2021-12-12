//Given an integer array nums, design an algorithm to randomly shuffle the array
//. All permutations of the array should be equally likely as a result of the shuf
//fling. 
//
// Implement the Solution class: 
//
// 
// Solution(int[] nums) Initializes the object with the integer array nums. 
// int[] reset() Resets the array to its original configuration and returns it. 
//
// int[] shuffle() Returns a random shuffling of the array. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["Solution", "shuffle", "reset", "shuffle"]
//[[[1, 2, 3]], [], [], []]
//Output
//[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]
//
//Explanation
//Solution solution = new Solution([1, 2, 3]);
//solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
//                       // Any permutation of [1,2,3] must be equally likely to
// be returned.
//                       // Example: return [3, 1, 2]
//solution.reset();      // Resets the array back to its original configuration 
//[1,2,3]. Return [1, 2, 3]
//solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Examp
//le: return [1, 3, 2]
//
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 200 
// -106 <= nums[i] <= 106 
// All the elements of nums are unique. 
// At most 5 * 104 calls in total will be made to reset and shuffle. 
// 
// Related Topics Array Math Randomized 
// 👍 461 👎 473


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution ： Fisher-Yates，洗牌算法
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> backup;
    Solution(vector<int>& nums) {
        backup = nums;
    }

    vector<int> reset() {
        return backup;
    }

    vector<int> shuffle() {
        vector<int> res = backup;
        for (int i = 0; i < res.size(); i++) {
            // int idx = rand() % res.size(); // 不算真正的随机分布
            int idx = i + rand() % (res.size() - i); // 这里表示的是从(i+1,end)选取随机下标
            swap(res[idx], res[i]);
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
//leetcode submit region end(Prohibit modification and deletion)
