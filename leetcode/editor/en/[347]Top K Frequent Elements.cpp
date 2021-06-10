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


/*
 * soultion 2: quick select
 * time: O(n)
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

//leetcode submit region end(Prohibit modification and deletion)
