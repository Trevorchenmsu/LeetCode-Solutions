//(This problem is an interactive problem.) 
//
// You may recall that an array A is a mountain array if and only if: 
//
// 
// A.length >= 3 
// There exists some i with 0 < i < A.length - 1 such that:
// 
// A[0] < A[1] < ... A[i-1] < A[i] 
// A[i] > A[i+1] > ... > A[A.length - 1] 
// 
// 
// 
//
// Given a mountain array mountainArr, return the minimum index such that mounta
//inArr.get(index) == target. If such an index doesn't exist, return -1. 
//
// You can't access the mountain array directly. You may only access the array u
//sing a MountainArray interface: 
//
// 
// MountainArray.get(k) returns the element of the array at index k (0-indexed).
// 
// MountainArray.length() returns the length of the array. 
// 
//
// Submissions making more than 100 calls to MountainArray.get will be judged Wr
//ong Answer. Also, any solutions that attempt to circumvent the judge will result
// in disqualification. 
//
// 
// 
//
// 
// Example 1: 
//
// 
//Input: array = [1,2,3,4,5,3,1], target = 3
//Output: 2
//Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum
// index, which is 2. 
//
// Example 2: 
//
// 
//Input: array = [0,1,2,4,2,1], target = 3
//Output: -1
//Explanation: 3 does not exist in the array, so we return -1.
// 
//
// 
// Constraints: 
//
// 
// 3 <= mountain_arr.length() <= 10000 
// 0 <= target <= 10^9 
// 0 <= mountain_arr.get(index) <= 10^9 
// 
// Related Topics Binary Search 
// 👍 499 👎 39


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int len = mountainArr.length();
        int max_idx = findMaxIndex(mountainArr, len);

        // search for left side
        int res = binarySearchLeft(mountainArr, target, 0, max_idx);
        if (res != -1) return res;

        // search for right side
        return binarySearchRight(mountainArr, target, max_idx, len - 1);;
    }

private:
    int findMaxIndex(MountainArray &mountainArr, int n) {
        int start = 0, end = n - 1;

        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (mountainArr.get(mid) > mountainArr.get(mid + 1))
                end = mid;
            else
                start = mid;
        }

        return start > end ? start : end;
    }

    int binarySearchLeft(MountainArray &mountainArr, int target, int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;

            if (mountainArr.get(mid) == target)
                return mid;
            else if (mountainArr.get(mid) > target)
                end = mid;
            else
                start = mid;
        }

        if (mountainArr.get(start) == target)
            return start;

        if (mountainArr.get(end) == target)
            return end;

        return -1;
    }

    int binarySearchRight(MountainArray &mountainArr, int target, int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;

            if (mountainArr.get(mid) == target)
                return mid;
            else if (mountainArr.get(mid) > target)
                start = mid;
            else
                end = mid;
        }

        if (mountainArr.get(start) == target)
            return start;

        if (mountainArr.get(end) == target)
            return end;

        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
