//Given an integer array instructions, you are asked to create a sorted array fr
//om the elements in instructions. You start with an empty container nums. For eac
//h element from left to right in instructions, insert it into nums. The cost of e
//ach insertion is the minimum of the following: 
//
// 
// The number of elements currently in nums that are strictly less than instruct
//ions[i]. 
// The number of elements currently in nums that are strictly greater than instr
//uctions[i]. 
// 
//
// For example, if inserting element 3 into nums = [1,2,3,5], the cost of insert
//ion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3)
// and nums will become [1,2,3,3,5]. 
//
// Return the total cost to insert all elements from instructions into nums. Sin
//ce the answer may be large, return it modulo 109 + 7 
//
// 
// Example 1: 
//
// 
//Input: instructions = [1,5,6,2]
//Output: 1
//Explanation: Begin with nums = [].
//Insert 1 with cost min(0, 0) = 0, now nums = [1].
//Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
//Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
//Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
//The total cost is 0 + 0 + 0 + 1 = 1. 
//
// Example 2: 
//
// 
//Input: instructions = [1,2,3,6,5,4]
//Output: 3
//Explanation: Begin with nums = [].
//Insert 1 with cost min(0, 0) = 0, now nums = [1].
//Insert 2 with cost min(1, 0) = 0, now nums = [1,2].
//Insert 3 with cost min(2, 0) = 0, now nums = [1,2,3].
//Insert 6 with cost min(3, 0) = 0, now nums = [1,2,3,6].
//Insert 5 with cost min(3, 1) = 1, now nums = [1,2,3,5,6].
//Insert 4 with cost min(3, 2) = 2, now nums = [1,2,3,4,5,6].
//The total cost is 0 + 0 + 0 + 0 + 1 + 2 = 3.
// 
//
// Example 3: 
//
// 
//Input: instructions = [1,3,3,3,2,4,2,1,2]
//Output: 4
//Explanation: Begin with nums = [].
//Insert 1 with cost min(0, 0) = 0, now nums = [1].
//Insert 3 with cost min(1, 0) = 0, now nums = [1,3].
//Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3].
//Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3,3].
//Insert 2 with cost min(1, 3) = 1, now nums = [1,2,3,3,3].
//Insert 4 with cost min(5, 0) = 0, now nums = [1,2,3,3,3,4].
//​​​​​​​Insert 2 with cost min(1, 4) = 1, now nums = [1,2,2,3,3,3,4].
//​​​​​​​Insert 1 with cost min(0, 6) = 0, now nums = [1,1,2,2,3,3,3,4].
//​​​​​​​Insert 2 with cost min(2, 4) = 2, now nums = [1,1,2,2,2,3,3,3,4].
//The total cost is 0 + 0 + 0 + 0 + 1 + 0 + 1 + 0 + 2 = 4.
// 
//
// 
// Constraints: 
//
// 
// 1 <= instructions.length <= 105 
// 1 <= instructions[i] <= 105 
// Related Topics Binary Search Binary Indexed Tree Segment Tree Ordered Map 
// 👍 357 👎 51


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        int n = instructions.size();
        for (int i=0; i<n; i++)
            sorted[i] = instructions[i];

        divideConquer(instructions, 0, n-1);
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            res += min(numSmaller[i], i - count[instructions[i]] - numSmaller[i]);
            res %= M;
            count[instructions[i]]++;
        }
        return res;
    }

private:
    int numSmaller[100005];
    int temp[100005];
    int count[100005];
    int sorted[100005];
    int M = 1e9+7;
    void divideConquer(vector<int> &nums, int start, int end) {
        if (start == end) return;

        int mid = start + (end - start) / 2;
        divideConquer(nums, start, mid);
        divideConquer(nums, mid + 1, end);

        for (int i = mid + 1; i <= end; i++) {
            auto iter = lower_bound(sorted + start, sorted + mid + 1, nums[i]);
            numSmaller[i] += iter - (sorted + start);
        }

        mergeSort(start, mid, end);
    }

    void mergeSort(int start, int mid, int end) {
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

        for (int i = 0; i < end - start + 1; i++)
            sorted[start + i] = temp[i];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
