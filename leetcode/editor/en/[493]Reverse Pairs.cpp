//Given an integer array nums, return the number of reverse pairs in the array. 
//
//
// A reverse pair is a pair (i, j) where 0 <= i < j < nums.length and nums[i] > 
//2 * nums[j]. 
//
// 
// Example 1: 
// Input: nums = [1,3,2,3,1]
//Output: 2
// Example 2: 
// Input: nums = [2,4,3,5,1]
//Output: 3
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 5 * 104 
// 231 <= nums[i] <= 231 - 1 
// 
// Related Topics Binary Search Divide and Conquer Sort Binary Indexed Tree Segm
//ent Tree 
// 👍 1392 👎 146


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: divide and conquer
 * time: O(nlog(logn))
 * space: O(n)
 * */
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size(), res = 0;
        vector<int> sorted = nums;
        divideConquer(nums, sorted, 0, n - 1, res);
        return res;
    }


private:
    int temp[50001];
    void divideConquer(vector<int> &nums, vector<int> &sorted, int start, int end, int &res) {
        if (start == end) return;

        int mid = start + (end - start) / 2;
        divideConquer(nums, sorted, start, mid, res);
        divideConquer(nums, sorted, mid + 1, end, res);

        for (int j = mid + 1; j <= end ; j++) {
            auto iter = upper_bound(sorted.begin() + start, sorted.begin() + mid + 1, 2 * (long) nums[j]);
            res += sorted.begin() + mid + 1 - iter;
        }

        mergeSort(sorted, start, mid, end);
    }

    void mergeSort(vector<int> &sorted, int start, int mid, int end) {
        int i = start, j = mid + 1, k = 0;

        while (i <= mid && j <= end) {
            if (sorted[i] <= sorted[j])
                temp[k++] = sorted[i++];
            else
                temp[k++] = sorted[j++];
        }

        while (i <= mid)
            temp[k++] = sorted[i++];

        while (j <= end)
            temp[k++] = sorted[j++];

        for (int i = 0; i < end - start + 1; i++)
            sorted[start + i] = temp[i];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
