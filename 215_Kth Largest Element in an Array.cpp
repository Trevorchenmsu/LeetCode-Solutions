/*
Solution: quick select
time: O(n) for average, O(n^2) in the worst case. n + n/2 + n/4  +… + 1 = O(n)
space: O(1)
*/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (nums.empty()) return -1;
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k + 1);
    }
private:
    int quickSelect(vector<int>& nums, int start, int end, int k) {
        if (start == end) return nums[start];

        int mid = start + (end - start) / 2;
        int pivot = nums[mid];

        // partition
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

        if (start + k - 1 <= j) {
            return quickSelect(nums, start, j, k);
        }
        if (start + k - 1 >= i) {
            return quickSelect(nums, i, end, k - (i - start));
        }

        return nums[j + 1];
    }
};

