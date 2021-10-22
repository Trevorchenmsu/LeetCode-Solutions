//Given an array nums with n objects colored red, white, or blue, sort them in-p
//lace so that objects of the same color are adjacent, with the colors in the orde
//r red, white, and blue. 
//
// We will use the integers 0, 1, and 2 to represent the color red, white, and b
//lue, respectively. 
//
// 
// Example 1: 
// Input: nums = [2,0,2,1,1,0]
//Output: [0,0,1,1,2,2]
// Example 2: 
// Input: nums = [2,0,1]
//Output: [0,1,2]
// Example 3: 
// Input: nums = [0]
//Output: [0]
// Example 4: 
// Input: nums = [1]
//Output: [1]
// 
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 300 
// nums[i] is 0, 1, or 2. 
// 
//
// 
// Follow up: 
//
// 
// Could you solve this problem without using the library's sort function? 
// Could you come up with a one-pass algorithm using only O(1) constant space? 
// 
// Related Topics Array Two Pointers Sort 
// 👍 5222 👎 298


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: three pointers, optimal
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size() - 1, i = 0;

        while (i <= right) {
            if (nums[i] == 0) {
                swap(nums[left++], nums[i++]);
            }
            else if (nums[i] == 1)
                i++;
            else
                swap(nums[i], nums[right--]);
        }
    }
};

/*
 * solution 2: merge sort
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }

        int n = nums.size();
        vector<int> bucket(n);
        mergeSort(nums, 0, n - 1, bucket);
    }

private:
    void mergeSort(vector<int> &nums, int start, int end, vector<int> &bucket) {
        if (start >= end) {
            return;
        }

        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid, bucket);
        mergeSort(nums, mid + 1, end, bucket);

        int idx = start, i = start, j = mid + 1;
        while (i <= mid && j <= end) {
            if (nums[i] <= nums[j]) {
                bucket[idx++] = nums[i++];
            }
            else {
                bucket[idx++] = nums[j++];
            }
        }

        while (i <= mid) {
            bucket[idx++] = nums[i++];
        }

        while (j <= end) {
            bucket[idx++] = nums[j++];
        }

        for (int i = start; i <= end; i++) {
            nums[i] = bucket[i];
        }
    }
};

/*
 * solution 3: quick sort
 * time: O(nlogn)
 * space: O(logn)
 * */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }

        quickSort(nums, 0, nums.size() - 1);
    }

private:
    void quickSort(vector<int> &nums, int start, int end) {
        if (start >= end) {
            return;
        }

        // partition
        int mid = start + (end - start) / 2;
        int pivot = nums[mid];
        int i = start, j = end;
        while (i <= j) {
            while (i <= j && nums[i] < pivot) {
                i++;
            }

            while (i <= j && nums[j] > pivot) {
                j--;
            }

            if (i <= j) {
                swap(nums[i++], nums[j--]);
            }
        }

        quickSort(nums, start, j);
        quickSort(nums, i, end);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
