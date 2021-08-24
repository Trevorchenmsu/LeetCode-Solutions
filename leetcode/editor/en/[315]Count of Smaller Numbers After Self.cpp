//You are given an integer array nums and you have to return a new counts array.
// The counts array has the property where counts[i] is the number of smaller elem
//ents to the right of nums[i]. 
//
// 
// Example 1: 
//
// 
//Input: nums = [5,2,6,1]
//Output: [2,1,1,0]
//Explanation:
//To the right of 5 there are 2 smaller elements (2 and 1).
//To the right of 2 there is only 1 smaller element (1).
//To the right of 6 there is 1 smaller element (1).
//To the right of 1 there is 0 smaller element.
// 
//
// Example 2: 
//
// 
//Input: nums = [-1]
//Output: [0]
// 
//
// Example 3: 
//
// 
//Input: nums = [-1,-1]
//Output: [0,0]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// -104 <= nums[i] <= 104 
// 
// Related Topics Binary Search Divide and Conquer Sort Binary Indexed Tree Segm
//ent Tree 
// 👍 3481 👎 110


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution: divide and conquer, merge sort
 * time: O(nlogn)
 * space: O(n)
 * */

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted = nums;
        vector<int> res(n, 0);
        divideConquer(nums, sorted, res, 0, n - 1);
        return res;
    }

    void divideConquer(vector<int>& nums, vector<int>& sorted, vector<int>& res, int start, int end) {
        if (start == end)
            return;

        int mid = start + (end - start) / 2;
        divideConquer(nums, sorted, res, start, mid);
        divideConquer(nums, sorted, res, mid + 1, end);

        /*
         * 在分治的过程中，复制原始数组，对原始数组进行归并排序。为什么要排序？
         *
         * */
        // 起点为什么是begin + mid + 1？因为我们想在右侧找大于等于val的下界。
        // 中点为什么是begin + end + 1？因为lower_bound需要的是超尾位置，而end只是最后一个元素的位置，需要加1获得超尾位置。
        for (int i = start; i <= mid; i++) {
            int val = nums[i];
            auto pos = lower_bound(sorted.begin() + mid + 1, sorted.begin() + end + 1, val);
            res[i] += pos - (sorted.begin() + mid + 1);
        }

        mergeSort(start, mid, end, sorted);
    }

    void mergeSort(int start, int mid, int end, vector<int> &sorted) {
        vector<int> temp(end - start + 1);
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

        for (int i = 0; i < temp.size(); i++) {
            sorted[start++] = temp[i];
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
