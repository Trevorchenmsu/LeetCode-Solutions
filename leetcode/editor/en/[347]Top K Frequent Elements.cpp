//Given an integer array nums and an integer k, return the k most frequent eleme
//nts. You may return the answer in any order. 
//
// 
// Example 1: 
// Input: nums = [1,1,1,2,2,3], k = 2
//Output: [1,2]
// Example 2: 
// Input: nums = [1], k = 1
//Output: [1]
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// k is in the range [1, the number of unique elements in the array]. 
// It is guaranteed that the answer is unique. 
// 
//
// 
// Follow up: Your algorithm's time complexity must be better than O(n log n), w
//here n is the array's size. 
// Related Topics Hash Table Heap 
// 👍 5147 👎 274


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * soultion 1: min heap
 * time: O(nlogk)
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnts;

        for (auto &num : nums) // O(n)
            cnts[num]++;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        for (auto &[num, cnt] : cnts) { // O(nlogk)
            pq.push({cnt, num});
            if (pq.size() > k)
                pq.pop();
        }

        vector<int> res;
        while (!pq.empty()) {  // O(klogk)
            res.push_back(pq.top()[1]);
            pq.pop();
        }

        return res;
    }
};

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnts = defaultdict(int)
        for num in nums:
        cnts[num] += 1

        min_heap = []
        heapq.heapify(min_heap)

        for num, cnt in cnts.items():
                heapq.heappush(min_heap, (cnt, num))
        if len(min_heap) > k:
        heapq.heappop(min_heap)

        ret = []
        while len(min_heap) > 0:
        ret.append(min_heap[0][1])
        heapq.heappop(min_heap)

        return ret
/*
 * soultion 2: quick select
 * time: 平均为O(n)，最差为O(n^2)，当数组元素全部一样或者全递增或者全递减的情况，是最坏情况。
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnts;

        for (auto &num : nums) // O(n)
            cnts[num]++;

        vector<vector<int>> cnt_num_pairs;
        for (auto &[num, cnt] : cnts) // O(L), the length of unique element
            cnt_num_pairs.push_back({cnt, num});

        int n = cnt_num_pairs.size();
        auto k_element = quickSelect(cnt_num_pairs, 0, n - 1, n - (k - 1)); // O(n)

        vector<int> res;
        for (auto &[num, cnt] : cnts) // O(L)
            if (cnt >= k_element[0])
                res.push_back(num);

        return res;
    }

    vector<int> quickSelect(vector<vector<int>> &nums, int start, int end, int k) {
        if (start == end) return nums[start];

        // partition
        int i = start, j = end;
        int mid = (start + end) / 2;
        vector<int> pivot = nums[mid];

        while (i <= j) {
            while (i <= j && nums[i][0] < pivot[0])
                i++;

            while (i <= j && nums[j][0] > pivot[0])
                j--;

            if (i <= j)
                swap(nums[i++], nums[j--]);
        }

        if (start + k - 1 <= j)
            return quickSelect(nums, start, j, k);

        if (start + k - 1 >= i)
            return quickSelect(nums, i, end, k - (i - start));

        return nums[j + 1];
    }
};

/*
 * soultion 3: quick select，模板优化
 * time: 平均为O(n)，最差为O(n^2)，当数组元素全部一样或者全递增或者全递减的情况，是最坏情况。
 * space: O(n)
 *
 * */

class Solution {
public:
    unordered_map<int, int> cnts;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        for (auto &num : nums) // O(n)
            cnts[num]++;

        vector<int> unique;
        for (auto &[num, cnt] : cnts) // O(L), the length of unique element
            unique.push_back(num);

        int n = unique.size();
        auto k_freq = quickSelect(unique, 0, n - 1, n - (k - 1)); // O(n)

        vector<int> res;
        for (auto &[num, cnt] : cnts) // O(L)
            if (cnt >= k_freq)
                res.push_back(num);

        return res;
    }

    int quickSelect(vector<int> &unique, int start, int end, int k) {
        if (start == end) return cnts[unique[start]];

        // partition
        int i = start, j = end;
        int mid = (start + end) / 2;
        int pivot = cnts[unique[mid]];

        while (i <= j) {
            while (i <= j && cnts[unique[i]] < pivot)
                i++;

            while (i <= j && cnts[unique[j]] > pivot)
                j--;

            if (i <= j)
                swap(unique[i++], unique[j--]);
        }

        if (start + k - 1 <= j)
            return quickSelect(unique, start, j, k);

        if (start + k - 1 >= i)
            return quickSelect(unique, i, end, k - (i - start));

        return cnts[unique[j + 1]];
    }
};

/*
 * soultion 4: quick select，比解法2和解法3的快选版本更优， optimal
 * time: 平均为O(n)，最差为O(n^2)，当数组元素全部一样或者全递增或者全递减的情况，是最坏情况。
 * space: O(n)
 *
 * */
class Solution {
public:
    unordered_map<int, int> cnts;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        for (auto &num : nums) // O(n)
            cnts[num]++;

        vector<int> unique;
        for (auto &[num, cnt] : cnts) // O(L), the length of unique element
            unique.push_back(num);

        int n = unique.size();
        auto k_idx = quickSelect(unique, 0, n - 1, n - (k - 1)); // O(n)

        vector<int> res (unique.begin() + k_idx, unique.end());

        return res;
    }

    int quickSelect(vector<int> &unique, int start, int end, int k) {
        if (start == end) return start;

        // partition
        int i = start, j = end;
        int mid = (start + end) / 2;
        int pivot = cnts[unique[mid]];

        while (i <= j) {
            while (i <= j && cnts[unique[i]] < pivot)
                i++;

            while (i <= j && cnts[unique[j]] > pivot)
                j--;

            if (i <= j)
                swap(unique[i++], unique[j--]);
        }

        if (start + k - 1 <= j)
            return quickSelect(unique, start, j, k);

        if (start + k - 1 >= i)
            return quickSelect(unique, i, end, k - (i - start));

        return j + 1;
    }
};

/*
 * solution 5: bucket sort, 在java中因为可以用链表的下标，所以是最优解，在C++中链表无法用下标，所以比较慢
 * time: O(nk)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 统计频率
        unordered_map<int, int> numCnt;
        for (auto & num : nums) numCnt[num]++;

        // 每个频率为一个桶，桶下面有多个元素均为这个频率，因为频率是放在桶的index，所以已经自动排序了
        vector<vector<int>> bucket (nums.size() + 1);
        for (auto &[num, cnt] : numCnt) {
            bucket[cnt].push_back(num);
        }

        vector<int> res;
        for (size_t i = nums.size(); i >= 0; i--) {
            // bucket[i].size()这里可以过滤掉桶的idx上没有元素的情况
            for (size_t j = 0; j < bucket[i].size(); j++) {
                res.push_back(bucket[i][j]);
                if (res.size() == k) return res;
            }
        }
        return res;
    }
};

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnts = defaultdict(int)
        for num in nums: cnts[num] += 1

        bucket = [[] for i in range(len(nums) + 1)]
        for num, cnt in cnts.items():
            bucket[cnt].append(num)

        ret = []
        for i in range(len(nums), 0, -1):
            for j in range(len(bucket[i])):
                ret.append(bucket[i][j])
                if len(ret) == k: return ret

        return ret
//leetcode submit region end(Prohibit modification and deletion)
