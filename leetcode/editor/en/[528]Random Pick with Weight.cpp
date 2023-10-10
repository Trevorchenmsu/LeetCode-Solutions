//You are given a 0-indexed array of positive integers w where w[i] describes th
//e weight of the ith index. 
//
// You need to implement the function pickIndex(), which randomly picks an index
// in the range [0, w.length - 1] (inclusive) and returns it. The probability of p
//icking an index i is w[i] / sum(w). 
//
// 
// For example, if w = [1, 3], the probability of picking index 0 is 1 / (1 + 3)
// = 0.25 (i.e., 25%), and the probability of picking index 1 is 3 / (1 + 3) = 0.7
//5 (i.e., 75%). 
// 
//
// 
// Example 1: 
//
// 
//Input
//["Solution","pickIndex"]
//[[[1]],[]]
//Output
//[null,0]
//
//Explanation
//Solution solution = new Solution([1]);
//solution.pickIndex(); // return 0. The only option is to return 0 since there 
//is only one element in w.
// 
//
// Example 2: 
//
// 
//Input
//["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
//[[[1,3]],[],[],[],[],[]]
//Output
//[null,1,1,1,1,0]
//
//Explanation
//Solution solution = new Solution([1, 3]);
//solution.pickIndex(); // return 1. It is returning the second element (index =
// 1) that has a probability of 3/4.
//solution.pickIndex(); // return 1
//solution.pickIndex(); // return 1
//solution.pickIndex(); // return 1
//solution.pickIndex(); // return 0. It is returning the first element (index = 
//0) that has a probability of 1/4.
//
//Since this is a randomization problem, multiple answers are allowed.
//All of the following outputs can be considered correct:
//[null,1,1,1,1,0]
//[null,1,1,1,1,1]
//[null,1,1,1,0,0]
//[null,1,1,1,0,1]
//[null,1,0,1,0,0]
//......
//and so on.
// 
//
// 
// Constraints: 
//
// 
// 1 <= w.length <= 104 
// 1 <= w[i] <= 105 
// pickIndex will be called at most 104 times. 
// 
// Related Topics Math Binary Search Prefix Sum Randomized 
// 👍 952 👎 420


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: prefix sum + binary search
 * time: O(n)
 * space: O(n)
 * */
class Solution {
    vector<int> prefixSum;
public:
    Solution(vector<int>& w) {
        prefixSum.resize(w.size());
        prefixSum[0] = w[0];
        for (int i = 1; i < w.size(); ++i)
        {
            prefixSum[i] = prefixSum[i - 1] + w[i];
        }
    }

    int pickIndex() {
        int random_idx = rand() % prefixSum.back();
        int res_idx = binarySearch(random_idx);
        return res_idx;
    }

    int binarySearch(int target) {
        int start = 0, end = prefixSum.size() - 1;
        while (start + 1 < end)
        {
            int mid = start + (end - start) / 2;
            if (prefixSum[mid] > target)
                end = mid;
            else start = mid;
        }

        if (prefixSum[start] > target)
            return start;
        else return end;
    }
};


class Solution:

    def __init__(self, w: List[int]):
        self.prefixSum = w
        for i in range(1, len(w)):
            self.prefixSum[i] = self.prefixSum[i - 1] + w[i]

    def pickIndex(self) -> int:
        rand_idx = random.random() * self.prefixSum[-1]
        res_idx = self.binarySearch(rand_idx)
        return res_idx

    def binarySearch(self, target):
        start, end = 0, len(self.prefixSum) - 1

        while start + 1 < end:
            mid = start + (end - start) // 2
            if self.prefixSum[mid] > target: end = mid
            else: start = mid

        if self.prefixSum[start] > target: return start
        else: return end
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
//leetcode submit region end(Prohibit modification and deletion)
