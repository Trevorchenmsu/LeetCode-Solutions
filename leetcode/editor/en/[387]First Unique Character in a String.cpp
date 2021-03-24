//Given a string, find the first non-repeating character in it and return its in
//dex. If it doesn't exist, return -1. 
//
// Examples: 
//
// 
//s = "leetcode"
//return 0.
//
//s = "loveleetcode"
//return 2.
// 
//
// 
//
// Note: You may assume the string contains only lowercase English letters. 
// Related Topics Hash Table String 
// 👍 2774 👎 139


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> cnt(256);

        for (auto& c: s) {
            cnt[c - 'a']++;
        }

        for (int i = 0; i < s.length(); i++) {
            if (cnt[s[i] - 'a'] == 1)
                return i;
        }

        return -1;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
