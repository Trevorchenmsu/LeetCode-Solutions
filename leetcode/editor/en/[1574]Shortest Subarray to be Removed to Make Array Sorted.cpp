//Given an integer array arr, remove a subarray (can be empty) from arr such tha
//t the remaining elements in arr are non-decreasing. 
//
// A subarray is a contiguous subsequence of the array. 
//
// Return the length of the shortest subarray to remove. 
//
// 
// Example 1: 
//
// 
//Input: arr = [1,2,3,10,4,2,3,5]
//Output: 3
//Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The 
//remaining elements after that will be [1,2,3,3,5] which are sorted.
//Another correct solution is to remove the subarray [3,10,4]. 
//
// Example 2: 
//
// 
//Input: arr = [5,4,3,2,1]
//Output: 4
//Explanation: Since the array is strictly decreasing, we can only keep a single
// element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] o
//r [4,3,2,1].
// 
//
// Example 3: 
//
// 
//Input: arr = [1,2,3]
//Output: 0
//Explanation: The array is already non-decreasing. We do not need to remove any
// elements.
// 
//
// Example 4: 
//
// 
//Input: arr = [1]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= arr.length <= 10^5 
// 0 <= arr[i] <= 10^9 
// 
// Related Topics Array Binary Search 
// 👍 516 👎 17


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        if (arr.size() <= 1) return 0;
        int n = arr.size();

        int leftEnd = 0;
        for (; leftEnd < n - 1; leftEnd++) {
            if (arr[leftEnd] > arr[leftEnd + 1])
                break;
        }
        if (leftEnd == n - 1) return 0;

        int rightStart = n - 1;
        for (; rightStart > 1; rightStart--) { // why boundary is 1?
            if (arr[rightStart] < arr[rightStart - 1])
                break;
        }

        if (arr[leftEnd] <= arr[rightStart])
            return rightStart - leftEnd - 1;

        // delete subarray after leftEnd (delete right part)
        // or subarray before rightStart (delete left part)
        // pick the smaller part
        int res = min(n - 1 - leftEnd, rightStart);
        for (int i = 0; i <= leftEnd; i++) {
            for (int j = rightStart; j < n; j++) {
                if (arr[i] <= arr[j]) {
                    // we only care about the first case because the rest will be larger
                    res = min(res, j - i - 1);
                    break;
                }
            }
        }

        return res;
    }
};


/*
 * solution 2: binary search
 * time: O(nlogn)
 * space: O(1)
 * */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        if (arr.size() <= 1) return 0;
        int n = arr.size();

        int leftEnd = 0;
        for (; leftEnd < n - 1; leftEnd++) {
            if (arr[leftEnd] > arr[leftEnd + 1])
                break;
        }
        if (leftEnd == n - 1) return 0;

        int rightStart = n - 1;
        for (; rightStart > 1; rightStart--) { // why boundary is 1?
            if (arr[rightStart] < arr[rightStart - 1])
                break;
        }

        if (arr[leftEnd] <= arr[rightStart])
            return rightStart - leftEnd - 1;

        // delete subarray after leftEnd (delete right part)
        // or subarray before rightStart (delete left part)
        // pick the smaller part
        int res = min(n - 1 - leftEnd, rightStart);
        for (int i = 0; i <= leftEnd; i++) {
            int j = findFirstBigIndex(arr, rightStart, n - 1, arr[i]);
            res = min(res, j - i - 1);
        }

        return res;
    }

private:
    int findFirstBigIndex(vector<int> &arr, int left, int right, int target) {
        int start = left, end = right;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (arr[mid] < target)
                start = mid + 1;
            else {
                if (mid == left || arr[mid - 1] < target)
                    return mid;
                end = mid - 1;
            }
        }

        return INT_MAX;
    }
};



/*
 * solution 3: binary search
 * time: O(nlogn)
 * space: O(1)
 * */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        if (arr.size() <= 1) return 0;
        int n = arr.size();

        int leftEnd = 0;
        for (; leftEnd < n - 1; leftEnd++) {
            if (arr[leftEnd] > arr[leftEnd + 1])
                break;
        }
        if (leftEnd == n - 1) return 0;

        int rightStart = n - 1;
        for (; rightStart > 0; rightStart--) { // why boundary is 1?
            if (arr[rightStart] < arr[rightStart - 1])
                break;
        }

        if (arr[leftEnd] <= arr[rightStart])
            return rightStart - leftEnd - 1;

        // delete subarray after leftEnd (delete right part)
        // or subarray before rightStart (delete left part)
        // pick the smaller part
        int res = min(n - 1 - leftEnd, rightStart);
        for (int i = 0; i <= leftEnd; i++) {
            if (rightStart - i - 1 >= res)
                continue;
            int j = findFirstBigIndex(arr, rightStart, n - 1, arr[i]);
            res = min(res, j - i - 1);
        }

        return res;
    }

private:
    int findFirstBigIndex(vector<int> &arr, int start, int end, int target) {
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (arr[mid] < target)
                start = mid + 1;
            else {
                end = mid - 1;
            }
        }

        return start;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
