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
 * solution 1: binary search,
 * time: O(n^2*logn)
 * space: O(logn)
 * */

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.size() < 3) {
            return 0;
        }

        sort(nums.begin(), nums.end());

        int res = 0;

        for (int i = 0; i < nums.size() - 2; i++) {
            for (int j = i + 1; j < nums.size() - 1; j++) {
                auto iter = lower_bound(nums.begin() + j + 1, nums.end(), nums[i] + nums[j]);
                res += (iter - (nums.begin() + j + 1));
            }
        }

        return res;
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
 * solution 3: binary search
 * time: O(n^2*logn)
 * space: O(logn) for sorting
 * */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());

        int res = 0, n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int target = nums[i] + nums[j];
                int idx = binarySearch(nums, target, j + 1, n - 1);
                res += idx - j;
            }
        }

        return res;
    }

private:
    int binarySearch(vector<int>& nums, int target, int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end -  start) / 2;
            if (nums[mid] >= target)
                end = mid;
            else
                start = mid;
        }

        if (nums[end] < target)
            return end;

        if (nums[start] < target)
            return start;

        return start - 1;
    }
};


/*
 * solution 4: two pointers
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
                /*
                 * 为什么nums[left]+nums[right]大于nums[i]就可以认为三角形有效，且把right-left个都加入结果？
                 * 例子：[2,2,2,2,3,4]，假设L=0，R=4，i=5，nums[L]=2,nums[R]=3,nums[i]=4，满足上述条件
                 * 因为三角形条件之一是两边之和大于第三边。由于数组是有序的且L位于左边第一个，因此在L后面R前面的所有元素都是大于nums[L],
                 * 这也就说明，这些元素与nums[R]之和肯定会大于nums[i]，因为升序排列。所以我们可以把从L开始到R这段区间中的元素都算作是
                 * 一个有效的三角形。从例子看，当前case有4个三角形，即R-L=4-0=4。这一点代入例子就很清楚了。
                 *
                 * */
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


