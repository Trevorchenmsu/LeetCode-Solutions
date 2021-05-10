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
 * solution 1: brute force, TLE
 * time: O(n^2)
 * space: O(1)
 * */
//class Solution {
//public:
//    vector<int> countSmaller(vector<int>& nums) {
//        vector<int> res;
//
//        for (int i = 0; i < nums.size(); i++) {
//            int cnt = 0;
//            for (int j = i + 1; j < nums.size(); j++) {
//                if (nums[j] < nums[i])
//                    cnt++;
//            }
//            res.push_back(cnt);
//        }
//
//        return res;
//    }
//};


/*
 * solution 2: divide and conquer, merge sort
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
