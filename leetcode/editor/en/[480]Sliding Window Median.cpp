//The median is the middle value in an ordered integer list. If the size of the 
//list is even, there is no middle value. So the median is the mean of the two mid
//dle values. 
//
// 
// For examples, if arr = [2,3,4], the median is 3. 
// For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5. 
// 
//
// You are given an integer array nums and an integer k. There is a sliding wind
//ow of size k which is moving from the very left of the array to the very right. 
//You can only see the k numbers in the window. Each time the sliding window moves
// right by one position. 
//
// Return the median array for each window in the original array. Answers within
// 10-5 of the actual value will be accepted. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
//Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
//Explanation: 
//Window position                Median
//---------------                -----
//[1  3  -1] -3  5  3  6  7        1
// 1 [3  -1  -3] 5  3  6  7       -1
// 1  3 [-1  -3  5] 3  6  7       -1
// 1  3  -1 [-3  5  3] 6  7        3
// 1  3  -1  -3 [5  3  6] 7        5
// 1  3  -1  -3  5 [3  6  7]       6
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
//Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
// 
//
// 
// Constraints: 
//
// 
// 1 <= k <= nums.length <= 105 
// 231 <= nums[i] <= 231 - 1 
// 
// Related Topics Array Hash Table Sliding Window Heap (Priority Queue) 
// 👍 1732 👎 111


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two heaps
 * time: O(nlogk)
 * space: O(k)
 * */

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        priority_queue<int> lo; // max heap
        priority_queue<int, vector<int>, greater<int>> hi; // min heap
        unordered_map<int, int> hash_table;

        // 初始化两个堆，把窗框分为两段，左堆存较小的，右堆存较大的，保证左堆长度大于右堆
        int i = 0;
        for (; i < k; i++) {
            lo.push(nums[i]);
        }
        for (int j = 0; j < k / 2; j++) {
            hi.push(lo.top());
            lo.pop();
        }

        double median;

        while (true) {
            // 因为循环外已经得到第一个窗口了，所以可以优先考虑结果。在下一个循环的时候，就是另一个新的窗口。
            median = k & 1 ? (double)lo.top() : ((double)lo.top() + (double)hi.top()) * 0.5;
            medians.push_back(median);

            if (i == nums.size()) break;

            // 窗口的左右边界。balance表示左右堆长度的平衡情况。in表示右边界，out表示左边界
            int out_num = nums[i - k],
                    in_num = nums[i++],
                    balance = 0;

            // 如果左边界大于左堆顶，表示删除的元素在右堆，所以右堆少了个元素，balance加1，否则是左堆少了元素，balance减1.
            // 同时采用哈希表记录删除元素，用计数器
            balance += (out_num > lo.top()) ? 1 : -1;
            hash_table[out_num]++; // indicate out_num has been deleted

            // 窗口扩大增加元素。
            if (!lo.empty() && in_num <= lo.top()) {
                lo.push(in_num);
                balance++;
            } else {
                hi.push(in_num);
                balance--;
            }

            // 窗口调整，此时不删除元素。balance小于0表示左堆少了元素，所以将元素从右堆拿过来，反之。同时更新balance。
            if (balance < 0){ // lo need more elements
                lo.push(hi.top());
                hi.pop();
                balance++;
            }
            if (balance > 0) {
                hi.push(lo.top());
                lo.pop();
                balance--;
            }

            // 在这里，窗口已达到平衡，窗口长度为k

            // 窗口缩小删除元素。我们只关注堆顶的元素，因为只有堆顶的元素会对结果造成影响，所以当堆顶元素是删除元素时
            // 就要弹出，如果不是，就留在堆里面不管他。
            while (!lo.empty() && hash_table[lo.top()]){
                hash_table[lo.top()]--;
                lo.pop();
            }
            while (!hi.empty() && hash_table[hi.top()]){
                hash_table[hi.top()]--;
                hi.pop();
            }
        }
        return medians;
    }
};

/*
 * solution 2: multiset
 * time: O(nlogk)
 * space: O(k)
 * */
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        if (nums.empty() || nums.size() == 0) {
            return medians;
        }

        // small表示左堆，large表示右堆
        multiset<int> small, large;

        for (int i = 0; i < nums.size(); i++) {
            // 超出窗口，删除左边界。因为原数组无序，左边界可能在small或large
            if (i >= k) {
                auto iter_small = small.find(nums[i - k]);
                auto iter_large = large.find(nums[i - k]);

                if (iter_small != small.end()) {
                    small.erase(iter_small);
                }
                else if (iter_large != large.end()) {
                    large.erase(iter_large);
                }
            }

            // 如果左段长度短，需要优先放左段
            if (small.size() <= large.size()) {
                // 右边界小于large的最小值，放左段
                if (large.empty() || nums[i] < *large.begin()) {
                    small.insert(nums[i]);
                }
                    // 右边界大于large最小值，需要把large最小值拿出来给small后再加新元素到large
                else {
                    small.insert(*large.begin());
                    large.erase(large.begin());
                    large.insert(nums[i]);
                }
            }
                // 如果右段较短，需要放入右段
            else {
                if (nums[i] >= *small.rbegin()) {
                    large.insert(nums[i]);
                }
                else {
                    large.insert(*small.rbegin());
                    small.erase(--small.end());
                    small.insert(nums[i]);
                }
            }

            // 添加结果
            if (i >= k - 1) {
                double median = k & 1 ? (double) *small.rbegin() : ((double) *small.rbegin() + *large.begin()) / 2.0;
                medians.push_back(median);
            }
        }

        return medians;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
