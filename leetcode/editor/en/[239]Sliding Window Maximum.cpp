//You are given an array of integers nums, there is a sliding window of size k w
//hich is moving from the very left of the array to the very right. You can only s
//ee the k numbers in the window. Each time the sliding window moves right by one 
//position. 
//
// Return the max sliding window. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
//Output: [3,3,5,5,6,7]
//Explanation: 
//Window position                Max
//---------------               -----
//[1  3  -1] -3  5  3  6  7       3
// 1 [3  -1  -3] 5  3  6  7       3
// 1  3 [-1  -3  5] 3  6  7       5
// 1  3  -1 [-3  5  3] 6  7       5
// 1  3  -1  -3 [5  3  6] 7       6
// 1  3  -1  -3  5 [3  6  7]      7
// 
//
// Example 2: 
//
// 
//Input: nums = [1], k = 1
//Output: [1]
// 
//
// Example 3: 
//
// 
//Input: nums = [1,-1], k = 1
//Output: [1,-1]
// 
//
// Example 4: 
//
// 
//Input: nums = [9,11], k = 2
//Output: [11]
// 
//
// Example 5: 
//
// 
//Input: nums = [4,-2], k = 2
//Output: [4]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// -104 <= nums[i] <= 104 
// 1 <= k <= nums.length 
// 
// Related Topics Heap Sliding Window Dequeue 
// 👍 5693 👎 234


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sliding window + monotonic stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty() || nums.size() == 0) return res;
        deque<int> dq;

        for (int i = 0; i < nums.size(); ++i)
        {
            while (!dq.empty() && nums[i] > dq.back())
                dq.pop_back();
            dq.push_back(nums[i]);

            if (i < k - 1) continue;

            res.push_back(dq.front());

            if (dq.front() == nums[i - k + 1])
                dq.pop_front();
        }

        return res;
    }
};


//python中用deque库比用list快
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        res = []
        dq = []

        for i in range(len(nums)):
            while dq and nums[i] > dq[-1]:
                dq.pop()
            dq.append(nums[i])

        if i < k - 1: continue

        res.append(dq[0])

        if dq[0] == nums[i - k + 1]:
            dq.pop(0)

        return res


class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        res = []
        dq = deque([])

    for i in range(len(nums)):
        while dq and nums[i] > dq[-1]:
            dq.pop()
        dq.append(nums[i])

        if i < k - 1: continue

        res.append(dq[0])

        if dq[0] == nums[i - k + 1]:
            dq.popleft()

    return res



class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        dq = deque([])
        res = []

        for i, n in enumerate(nums):
            if dq and dq[0] < i - k + 1:
                dq.popleft()

            while dq and nums[dq[-1]] < n:
                dq.pop()

            dq.append(i)

            if i >= k - 1:
                res.append(nums[dq[0]])

        return res
//leetcode submit region end(Prohibit modification and deletion)
