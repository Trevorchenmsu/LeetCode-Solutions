//Given an array of characters chars, compress it using the following algorithm:
// 
//
// Begin with an empty string s. For each group of consecutive repeating charact
//ers in chars: 
//
// 
// If the group's length is 1, append the character to s. 
// Otherwise, append the character followed by the group's length. 
// 
//
// The compressed string s should not be returned separately, but instead be sto
//red in the input character array chars. Note that group lengths that are 10 or l
//onger will be split into multiple characters in chars. 
//
// After you are done modifying the input array, return the new length of the ar
//ray. 
//You must write an algorithm that uses only constant extra space.
// 
// Example 1: 
//
// 
//Input: chars = ["a","a","b","b","c","c","c"]
//Output: Return 6, and the first 6 characters of the input array should be: ["a
//","2","b","2","c","3"]
//Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3"
//.
// 
//
// Example 2: 
//
// 
//Input: chars = ["a"]
//Output: Return 1, and the first character of the input array should be: ["a"]
//Explanation: The only group is "a", which remains uncompressed since it's a si
//ngle character.
// 
//
// Example 3: 
//
// 
//Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
//Output: Return 4, and the first 4 characters of the input array should be: ["a
//","b","1","2"].
//Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
// 
//
// Example 4: 
//
// 
//Input: chars = ["a","a","a","b","b","a","a"]
//Output: Return 6, and the first 6 characters of the input array should be: ["a
//","3","b","2","a","2"].
//Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2"
//. Note that each group is independent even if two groups have the same character
//.
// 
//
// 
// Constraints: 
//
// 
// 1 <= chars.length <= 2000 
// chars[i] is a lower-case English letter, upper-case English letter, digit, or
// symbol. 
// 
// Related Topics Two Pointers String 
// 👍 1425 👎 3459


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int compress(vector<char>& chars) {
        string res = "";
        int left = 0, right = 0;

        for (; right <= chars.size(); right++) { // O(n)
            if (right < chars.size() && chars[right] == chars[left]) {
                continue;
            }

            if (right - left > 1) {
                res += (chars[left] + to_string(right - left));
            }
            else {
                res += chars[left];
            }

            left = right;
        }

        int i = chars.size() - 1;
        while (i >= 0) { // O(n)
            if (i >= res.size()) {
                chars.pop_back();
            }
            else {
                chars[i] = res[i];
            }
            i--;
        }

        return chars.size();
    }
};

/*
 * solution 2: brute force
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int compress(vector<char>& chars) {
        string res = "";
        int cnt = 1;
        for (int i = 0; i < chars.size(); i++) {

            if (i < chars.size() - 1 && chars[i] == chars[i + 1]) {
                cnt++;
            }
            else {
                if (cnt != 1) {
                    res.push_back(chars[i]);
                    res += to_string(cnt);
                    cnt = 1;
                }
                else {
                    res.push_back(chars[i]);
                }
            }
        }

        int size = chars.size();
        for (int i = 0; i < size; i++) {
            if (i < res.size() ) {
                chars[i] = res[i];
            }
            else {
                chars.pop_back();
            }
        }

        return chars.size();

    }
};
//leetcode submit region end(Prohibit modification and deletion)
