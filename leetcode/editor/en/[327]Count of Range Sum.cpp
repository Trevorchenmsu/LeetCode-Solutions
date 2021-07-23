//Given an integer array nums and two integers lower and upper, return the numbe
//r of range sums that lie in [lower, upper] inclusive. 
//
// Range sum S(i, j) is defined as the sum of the elements in nums between indic
//es i and j inclusive, where i <= j. 
//
// 
// Example 1: 
//
// 
//Input: nums = [-2,5,-1], lower = -2, upper = 2
//Output: 3
//Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respectiv
//e sums are: -2, -1, 2.
// 
//
// Example 2: 
//
// 
//Input: nums = [0], lower = 0, upper = 0
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -231 <= nums[i] <= 231 - 1 
// -105 <= lower <= upper <= 105 
// The answer is guaranteed to fit in a 32-bit integer. 
// 
// Related Topics Binary Search Divide and Conquer Sort Binary Indexed Tree Segm
//ent Tree 
// 👍 1054 👎 122


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: divide and conquer
 * time: O(nlog(logn))
 * space: O(n)
 * */
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size(), res = 0;
        vector<long> presum(n + 1);
        for (int i = 0; i < n; i++)
            presum[i + 1] = presum[i] + nums[i];

        divideConquer(presum, 0, n, lower, upper, res);

        return res;
    }

private:
    vector<long> temp = vector<long> (100001);
    void divideConquer(vector<long> &presum, int start, int end, int lower, int upper, int &res) {
        if (start == end)
            return;

        int mid = start + (end -  start) / 2;
        divideConquer(presum, start, mid, lower, upper, res);
        divideConquer(presum, mid + 1, end, lower, upper, res);

        for (int i = start; i <= mid; i++) {
            auto p1 = lower_bound(presum.begin() + mid + 1, presum.begin() + end + 1, presum[i] + lower);
            auto p2 = upper_bound(presum.begin() + mid + 1, presum.begin() + end + 1, presum[i] + upper);
            res += p2 - p1;
        }

        mergeSort(start, mid, end, presum);
    }

    void mergeSort(int start, int mid, int end, vector<long> &presum) {
        int i = start, j = mid + 1, k = 0;

        while (i <= mid && j <= end) {
            if (presum[i] <= presum[j])
                temp[k++] = presum[i++];
            else
                temp[k++] = presum[j++];
        }

        while (i <= mid)
            temp[k++] = presum[i++];

        while (j <= end)
            temp[k++] = presum[j++];

        for (int i = 0; i < end - start + 1; i++)
            presum[start + i] = temp[i];
    }
};

/*
 * solution 2: Segment Tree
 * time: O(nlog(logn))
 * space: O(n)
 * */

//leetcode submit region end(Prohibit modification and deletion)
