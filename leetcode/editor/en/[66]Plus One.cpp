//You are given a large integer represented as an integer array digits, where ea
//ch digits[i] is the ith digit of the integer. The digits are ordered from most s
//ignificant to least significant in left-to-right order. The large integer does n
//ot contain any leading 0's. 
//
// Increment the large integer by one and return the resulting array of digits. 
//
//
// 
// Example 1: 
//
// 
//Input: digits = [1,2,3]
//Output: [1,2,4]
//Explanation: The array represents the integer 123.
//Incrementing by one gives 123 + 1 = 124.
//Thus, the result should be [1,2,4].
// 
//
// Example 2: 
//
// 
//Input: digits = [4,3,2,1]
//Output: [4,3,2,2]
//Explanation: The array represents the integer 4321.
//Incrementing by one gives 4321 + 1 = 4322.
//Thus, the result should be [4,3,2,2].
// 
//
// Example 3: 
//
// 
//Input: digits = [0]
//Output: [1]
//Explanation: The array represents the integer 0.
//Incrementing by one gives 0 + 1 = 1.
//Thus, the result should be [1].
// 
//
// Example 4: 
//
// 
//Input: digits = [9]
//Output: [1,0]
//Explanation: The array represents the integer 9.
//Incrementing by one gives 9 + 1 = 10.
//Thus, the result should be [1,0].
// 
//
// 
// Constraints: 
//
// 
// 1 <= digits.length <= 100 
// 0 <= digits[i] <= 9 
// digits does not contain any leading 0's. 
// 
// Related Topics Array Math 
// 👍 2982 👎 3677


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: brute force
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if (digits.empty() || digits.size() == 0) {
            return {};
        }

        for (int i = digits.size() - 1; i >= 0; i--) {
            //这里很tricky，如果是小于9的数，只会加1一次，然后就可以直接返回，循环不会继续
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            // 如果加1后进位，不用考虑如何进位，只要把当前位置为0，因为在下个循环中，会考虑到
            // 这个进位
            else {
                digits[i] = 0;
            }
        }

        // 如果在for中没有返回，表示一直在进位，所以最后进位到新的数，因此左边加1
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
