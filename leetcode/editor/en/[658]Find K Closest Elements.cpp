//Given a sorted integer array arr, two integers k and x, return the k closest i
//ntegers to x in the array. The result should also be sorted in ascending order. 
//
//
// An integer a is closer to x than an integer b if: 
//
// 
// |a - x| < |b - x|, or 
// |a - x| == |b - x| and a < b 
// 
//
// 
// Example 1: 
// Input: arr = [1,2,3,4,5], k = 4, x = 3
//Output: [1,2,3,4]
// Example 2: 
// Input: arr = [1,2,3,4,5], k = 4, x = -1
//Output: [1,2,3,4]
// 
// 
// Constraints: 
//
// 
// 1 <= k <= arr.length 
// 1 <= arr.length <= 104 
// arr is sorted in ascending order. 
// -104 <= arr[i], x <= 104 
// 
// Related Topics Binary Search 
// 👍 2024 👎 324


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res = arr;

        while (res.size() > k) {
            if (abs(x - res.front()) <= abs(x - res.back()))
                res.pop_back();
            else
                res.erase(res.begin());
        }

        return res;
    }
};


/*
 * solution 2: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - 1;
        while (left < right) {
            if (right - left + 1 == k)
                break;

            if (abs(x - arr[left]) > abs(x - arr[right]))
                left++;
            else
                right--;
        }

        return vector<int> (arr.begin() + left, arr.begin() + left + k);
    }
};


/*
 * solution 3: binary search + two pointers
 * time: O(max(k,logn))
 * space: O(k)
 * */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        if (arr.size() == 1) return arr;
        int n = arr.size();

        // find index of elements closest to x
        int start = 0, end = n - 1;
        while (start + 1 < end) { // O(logn)
            int mid = start + (end - start) / 2;
            if (arr[mid] >= x)
                end = mid;
            else
                start = mid;
        }

        deque<int> res;
        int left = start, right = end;
        while (res.size() < k) { // O(k)
            if (right == n || (left >= 0 && (x - arr[left] <= arr[right] - x)))
                res.push_front(arr[left--]);
            else
                res.push_back(arr[right++]);

        }

        return vector<int>(res.begin(), res.end());
    }

};



/*
 * solution 4: binary search + sliding window
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int start = 0, end = arr.size() - k;
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (x - arr[mid] > arr[mid + k] - x)
                start = mid + 1;
            else end = mid;
        }

        return vector<int> (arr.begin() + start, arr.begin() + start + k);
    }

};
//leetcode submit region end(Prohibit modification and deletion)
