//Given an integer array arr, and an integer target, return the number of tuples
// i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target. 
//
// As the answer can be very large, return it modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
//Output: 20
//Explanation: 
//Enumerating by the values (arr[i], arr[j], arr[k]):
//(1, 2, 5) occurs 8 times;
//(1, 3, 4) occurs 8 times;
//(2, 2, 4) occurs 2 times;
//(2, 3, 3) occurs 2 times.
// 
//
// Example 2: 
//
// 
//Input: arr = [1,1,2,2,2,2], target = 5
//Output: 12
//Explanation: 
//arr[i] = 1, arr[j] = arr[k] = 2 occurs 12 times:
//We choose one 1 from [1,1] in 2 ways,
//and two 2s from [2,2,2,2] in 6 ways.
// 
//
// 
// Constraints: 
//
// 
// 3 <= arr.length <= 3000 
// 0 <= arr[i] <= 100 
// 0 <= target <= 300 
// 
// Related Topics Array Hash Table Two Pointers Sorting Counting 
// 👍 869 👎 139


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int MOD = 1e9 + 7;
    int threeSumMulti(vector<int>& arr, int target) {
        long long res = 0;
        sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size() - 2; ++i)
        {
            twoSum(arr, res, target - arr[i], i + 1, arr.size() - 1);
        }

        return (int) (res % MOD);
    }

    void twoSum(vector<int>& arr, long long& res, int target, int j, int k) {
        while (j < k)
        {
            int sum = arr[j] + arr[k];
            if (sum == target)
            {   int left = 1, right = 1;
                while (j + left < k && arr[j + left] == arr[j])
                {
                    ++left;
                }
                while (j + left <= k - right && arr[k - right] == arr[k])
                {
                    ++right;
                }
                /*
                当a[j]=a[k]时，例如下面。要采用组合的思路，第一个2可以与后面4个配对4个，第二个2可以与后面3个配对3个，以此类推
                4+3+2+1，然后用累加和的公式n*(n+1)/2，本题中n=k-j，n+1=k-j+1
                2 2 2 2 2
                j       k
                */
                res += arr[j] == arr[k] ? (k - j + 1) * (k - j) / 2: left * right;
                j += left;
                k -= right;
            }
            else if (sum < target)
            {
                j++;
            }
            else
            {
                k--;
            }
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
