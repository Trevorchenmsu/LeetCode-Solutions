//Given an integer array arr and a target value target, return the integer value
// such that when we change all the integers larger than value in the given array 
//to be equal to value, the sum of the array gets as close as possible (in absolut
//e difference) to target. 
//
// In case of a tie, return the minimum such integer. 
//
// Notice that the answer is not neccesarilly a number from arr. 
//
// 
// Example 1: 
//
// 
//Input: arr = [4,9,3], target = 10
//Output: 3
//Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's th
//e optimal answer.
// 
//
// Example 2: 
//
// 
//Input: arr = [2,3,5], target = 10
//Output: 5
// 
//
// Example 3: 
//
// 
//Input: arr = [60864,25176,27249,21296,20204], target = 56803
//Output: 11361
// 
//
// 
// Constraints: 
//
// 
// 1 <= arr.length <= 104 
// 1 <= arr[i], target <= 105 
// 
// Related Topics Array Binary Search 
// 👍 504 👎 71


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    vector<int>presum;
public:
    int findBestValue(vector<int>& arr, int target)
    {
        sort(arr.begin(),arr.end());

        presum.resize(arr.size());
        presum[0] = arr[0];
        for (int i=1; i<arr.size(); i++)
            presum[i] = presum[i-1]+arr[i];

        if (presum.back() <= target) return arr.back();

        int left = 0;
        int right = 1e5;

        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (helper(arr, mid)>=target)
                right = mid;
            else
                left = mid+1;
        }

        int a = helper(arr,left);
        int b = helper(arr,left-1);
        if (abs(a-target)<abs(target-b))
            return left;
        else
            return left-1;
    }

    long long helper(vector<int>&arr, int value)
    {
        auto iter = upper_bound(arr.begin(),arr.end(),value);
        int num = arr.end()-iter;
        if (iter-arr.begin()-1>=0)
            return presum[iter-arr.begin()-1]+(long long)num*value;
        else
            return (long long)num*value;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
