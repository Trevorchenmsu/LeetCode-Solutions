//You are playing the Bulls and Cows game with your friend. 
//
// You write down a secret number and ask your friend to guess what the number i
//s. When your friend makes a guess, you provide a hint with the following info: 
//
// 
// The number of "bulls", which are digits in the guess that are in the correct 
//position. 
// The number of "cows", which are digits in the guess that are in your secret n
//umber but are located in the wrong position. Specifically, the non-bull digits i
//n the guess that could be rearranged such that they become bulls. 
// 
//
// Given the secret number secret and your friend's guess guess, return the hint
// for your friend's guess. 
//
// The hint should be formatted as "xAyB", where x is the number of bulls and y 
//is the number of cows. Note that both secret and guess may contain duplicate dig
//its. 
//
// 
// Example 1: 
//
// 
//Input: secret = "1807", guess = "7810"
//Output: "1A3B"
//Explanation: Bulls are connected with a '|' and cows are underlined:
//"1807"
//  |
//"7810" 
//
// Example 2: 
//
// 
//Input: secret = "1123", guess = "0111"
//Output: "1A1B"
//Explanation: Bulls are connected with a '|' and cows are underlined:
//"1123"        "1123"
//  |      or     |
//"0111"        "0111"
//Note that only one of the two unmatched 1s is counted as a cow since the non-b
//ull digits can only be rearranged to allow one 1 to be a bull.
// 
//
// Example 3: 
//
// 
//Input: secret = "1", guess = "0"
//Output: "0A0B"
// 
//
// Example 4: 
//
// 
//Input: secret = "1", guess = "1"
//Output: "1A0B"
// 
//
// 
// Constraints: 
//
// 
// 1 <= secret.length, guess.length <= 1000 
// secret.length == guess.length 
// secret and guess consist of digits only. 
// 
// Related Topics Hash Table String Counting 
// 👍 1130 👎 1176


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string getHint(string secret, string guess) {
        int A = 0, B = 0;
        vector<int> cnts(10);

        for (int i = 0; i < secret.size(); i++) {
            if (secret[i] == guess[i]) {
                A++;
            }
            else {
                // secret的计数器递增。secret的计数是可以大于0的，表明仍未被匹配。这里要判断小于等于0
                // 是因为在guess中可能有多余的字符还未被匹配，光用等于0不足够考虑全部
                cnts[secret[i] - '0']++;
                if (cnts[secret[i] - '0'] <= 0) {
                    B++;
                }

                cnts[guess[i] - '0']--;
                if (cnts[guess[i] - '0'] >= 0) {
                    B++;
                }
            }
        }

        string res = to_string(A) + "A" + to_string(B) + "B";
        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
