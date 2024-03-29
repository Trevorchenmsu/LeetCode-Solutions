//You are given a 0-indexed integer array nums and an integer k. 
//
// You are initially standing at index 0. In one move, you can jump at most k st
//eps forward without going outside the boundaries of the array. That is, you can 
//jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive
//. 
//
// You want to reach the last index of the array (index n - 1). Your score is th
//e sum of all nums[j] for each index j you visited in the array. 
//
// Return the maximum score you can get. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,-1,-2,4,-7,3], k = 2
//Output: 7
//Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (und
//erlined above). The sum is 7.
// 
//
// Example 2: 
//
// 
//Input: nums = [10,-5,-2,4,0,3], k = 3
//Output: 17
//Explanation: You can choose your jumps forming the subsequence [10,4,3] (under
//lined above). The sum is 17.
// 
//
// Example 3: 
//
// 
//Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length, k <= 105 
// -104 <= nums[i] <= 104 
// 
// Related Topics Dequeue 
// 👍 384 👎 23


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sliding window + monotonic stack
 * time: O(n)
 * space: (n)
 * */
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        deque<pair<int, int>> dq;
        dq.push_back({nums[0], 0});

        for (int i = 1; i < n; i++) {
            /* 这里的k不是滑窗的大小，k只是跳的最远位置，所以窗口大小应该为k+1
              为什么这里要弹出dq.front()?因为front存储的是窗口的左边界，当出现新的右窗口边界时，就要更新左边界。
               在弹出front以后，顶替上来的front位置不一定是跟之前的front相临近的位置，而是从之前位置所跳到的和最大
               的位置，这是因为我们维护的是一个单调递减栈，在窗口范围内和比较小的最终都会被pop掉，留下和最大的位置。
               因为这个和最大的位置就可以作为下一个窗口的起跳点。
            */
            if (!dq.empty() && i - dq.front().second > k)
                dq.pop_front();

            /*
             * 这两步就是用来更新当前窗口内和最大的元素。当新位置加上起点的值更大时，就要把dq中较小位置弹出让位
             * 这里的curSteps就是我漏掉的求和，在每次遍历中都把和记录好。每次累加和没有关系，因为在单调栈中会降序排序，
             * 所有最终优先考虑的都是最大值。
             * */
            int score = dq.front().first + nums[i];
            while (!dq.empty() && curSteps > dq.back().first)
                dq.pop_back();

            // 所以最终插入单调栈尾部的不是单纯的数组值和idx，而是累加在那个idx的和及其idx
            dq.push_back({score, i});
        }

        // 这里返回的不能时dq.front().first，因为更大的和都是在back逐渐加进去的
        return dq.back().first;
    }
};


/*
 * solution 2: sliding window + monotonic stack, better solution，标准的单调栈和滑窗处理
 * time: O(n)
 * space: (n)
 * */

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        deque<int> dq;
        dq.push_back(0);

        for(int i = 1; i < nums.size(); i++) {
            nums[i] += nums[dq.front()];

            // 标准单调栈处理
            while (!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }

            // 标准滑窗处理，超出窗口后删除
            if(!dq.empty() && i - dq.front() >= k) {
                dq.pop_front();
            }

            // 标准单调栈加入元素
            dq.push_back(i);
        }

        return nums.back();
    }
};


/*
 * solution 3: sliding window + max heap, slower solution
 * time: O(nlogn)
 * space: (n)
 * */
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> pq;
        pq.push({nums[0], 0});

        for (int i = 1; i < n; i++) {
            // 这一步保证在当前元素的滑动范围内
            while (!pq.empty() && i - pq.top().second > k) {
                pq.pop();
            }

            // 为什么这一步可以一直更新nums[i]？堆顶元素的大小取决于我们加入的新元素
            // 如果nums[i]本身小于0，那么更新后的nums[i]肯定更小，所以堆顶还是保留之前的元素以及角标
            // 如果nums[i]大于0，则会替换新的堆顶元素，同时更新对应的i
            nums[i] = nums[i] + nums[pq.top().second];
            pq.push({nums[i], i});
        }
        return nums[n - 1];
    }
};

/*
 * solution 4: sliding window + max heap, slower than solution 3
 * time: O(nlogn)
 * space: (n)
 * */
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> score(n);
        priority_queue<vector<int>> maxHeap;
        score[0] = nums[0];
        maxHeap.push({nums[0], 0});

        for (int i = 1; i < n; i++) {
            while (i - maxHeap.top()[1] > k)
                maxHeap.pop();
            score[i] = nums[i] + maxHeap.top()[0];
            maxHeap.push({score[i], i});
        }

        return score[n - 1];
    }
};


//leetcode submit region end(Prohibit modification and deletion)
