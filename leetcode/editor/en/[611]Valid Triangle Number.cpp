//Given an array consists of non-negative integers, your task is to count the nu
//mber of triplets chosen from the array that can make triangles if we take them a
//s side lengths of a triangle.
//
// Example 1: 
// 
//Input: [2,2,3,4]
//Output: 3
//Explanation:
//Valid combinations are: 
//2,3,4 (using the first 2)
//2,3,4 (using the second 2)
//2,2,3
// 
// 
//
// Note: 
// 
// The length of the given array won't exceed 1000. 
// The integers in the given array are in the range of [0, 1000]. 
// 
// 
// Related Topics Array 
// 👍 1361 👎 106


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: backtrack, TLE
 * time: O(k*C(n, k))
 * space: O(C(n, k))/O(k)
 * */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.empty()) return 0;

        vector<int> path;
        backtrack(nums, path, 0);

        return cnt;
    }

private:
    int cnt;
    void backtrack(vector<int> &nums, vector<int> &path, int idx) {
        if (path.size() == 3) {
            if (validTriangle(path)) cnt++;
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(nums, path, i + 1);
            path.pop_back();
        }
    }

    bool validTriangle(vector<int> &arr) {
        int a = arr[0], b = arr[1], c = arr[2];

        if (a + b <= c || a + c <= b || b + c <= a)
            return false;

        return true;
    }
};



/*
 * solution 2: binary search,
 * time: O(n^2*logn)
 * space: O(logn)
 * */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.empty()) return 0;

        int n = nums.size(), res = 0;
        sort(nums.begin(), nums.end()); // O(nlogn)

        for (int i = 0; i < n; i++) { // O(n^2*logn)
            for (int j = i + 1; j < n; j++) {
                int sum = nums[i] + nums[j];

                int start = j + 1, end = n - 1;
                while (start + 1 < end) {
                    int mid = start + (end - start) / 2;

                    if (nums[mid] >= sum)
                        end = mid;
                    else
                        start = mid;
                }

                if (nums[end] < sum)
                    res += end - j;
                else if (start < n && nums[start] < sum)
                    res += start - j;
            }
        }

        return res;
    }

};



/*
 * solution 3: two pointers
 * time: O(n^2)
 * space: O(logn)
 * */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.empty()) return 0;

        int res = 0, n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = n - 1; i >= 2; --i) {
            int left = 0, right = i - 1;
            while (left < right) {
                if (nums[left] + nums[right] > nums[i]) {
                    res += right - left;
                    --right;
                } else {
                    ++left;
                }
            }
        }
        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)




