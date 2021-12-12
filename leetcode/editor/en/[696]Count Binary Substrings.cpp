//Give a binary string s, return the number of non-empty substrings that have th
//e same number of 0's and 1's, and all the 0's and all the 1's in these substring
//s are grouped consecutively. 
//
// Substrings that occur multiple times are counted the number of times they occ
//ur. 
//
// 
// Example 1: 
//
// 
//Input: s = "00110011"
//Output: 6
//Explanation: There are 6 substrings that have equal number of consecutive 1's 
//and 0's: "0011", "01", "1100", "10", "0011", and "01".
//Notice that some of these substrings repeat and are counted the number of time
//s they occur.
//Also, "00110011" is not a valid substring because all the 0's (and 1's) are no
//t grouped together.
// 
//
// Example 2: 
//
// 
//Input: s = "10101"
//Output: 4
//Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal nu
//mber of consecutive 1's and 0's.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 105 
// s[i] is either '0' or '1'. 
// 
// Related Topics Two Pointers String 
// 👍 2066 👎 361


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: brute force
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int countBinarySubstrings(string s) {
        int ones = 0, zeros = 0, res = 0;
        for (int i = 0; i < s.size(); i++) {
            // 先确定第一个元素是1还是0，然后计数器加1
            if (i == 0) {
                s[i] == '1'? ++ones : ++zeros;
            }
            else {
                // 如果当前元素是1，就得判断之前元素是否为1。如果是，计数器累积，如果不是，重置计数器为1
                if (s[i] == '1') {
                    ones = s[i - 1] == s[i]? ones + 1 : 1;
                    // 当更新完计数器后，判定是否为合理结果。如果前面为01,遇到1后，为011，1的个数大于0的个数，不合理。
                    // 如果前面为10，遇到1后，为101，1的个数重置为1，0的个数为1，合理，结果为01
                    // 如果前面为001，遇到1后，0和1的计数器相等为2，合理，结果为0011.这里的个数判断比较tricky
                    if (zeros >= ones) {
                        res++;
                    }
                }
                else {
                    zeros = s[i - 1] == s[i]? zeros + 1 : 1;
                    if (ones >= zeros) {
                        res++;
                    }
                }
            }
        }

        return res;
    }
};



/*
 * solution 2: brute force
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    int countBinarySubstrings(string s) {
        // pre表示上一个元素的计数器，cur比较当前元素的计数器
        int res = 0, pre = 0, cur = 1, n = s.size();

        for (int i = 1; i < n; i++) {
            // 当前元素与上一个元素相等，当前计数器加1
            if (s[i] == s[i - 1]) {
                ++cur;
            }
                // 当前元素与上一个元素不等，更新上一个元素计数器为当前元素计数器，重置当前计数器为1
            else {
                pre = cur;
                cur = 1;
            }

            // 比较上一个元素计数器和当前元素计数器大小，只要上一个元素计数器大于等于当前元素计数器，就合理
            // 为什么？例如110可得10，001可得01，1100合理，0011合理，11100可得1100，00011可得0011
            if (pre >= cur) {
                res++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
