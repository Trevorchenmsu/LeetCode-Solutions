//Given two strings s1 and s2, return true if s2 contains a permutation of s1, o
//r false otherwise. 
//
// In other words, return true if one of s1's permutations is the substring of s
//2. 
//
// 
// Example 1: 
//
// 
//Input: s1 = "ab", s2 = "eidbaooo"
//Output: true
//Explanation: s2 contains one permutation of s1 ("ba").
// 
//
// Example 2: 
//
// 
//Input: s1 = "ab", s2 = "eidboaoo"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= s1.length, s2.length <= 104 
// s1 and s2 consist of lowercase English letters. 
// 
// Related Topics Hash Table Two Pointers String Sliding Window 
// 👍 3036 👎 85


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table + sliding window
 * time: O(min(m, n-m))
 * space: O(1)
 * */
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
        }

        int m = s1.size(), n = s2.size();
        vector<int> counts1(26), counts2(26);
        for (int i = 0; i < m; i++) {
            counts1[s1[i] - 'a']++;
            counts2[s2[i] - 'a']++;
        }

        for (int i = 0; i < n - m; i++) {
            if (counts1 == counts2) {
                return true;
            }

            counts2[s2[i + m] - 'a']++;
            counts2[s2[i] - 'a']--;
        }

        return counts1 == counts2;
    }
};

/*
 * solution 2: hash table + sliding window
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        int cnt = m, left = 0;

        vector<int> counts(26);

        for (auto &ch : s1) {
            counts[ch - 'a']++;
        }

        for (int right = 0; right < n; right++) {
            // 大于0表示在s1中存在这个字符，所以cnt-1
            if (counts[s2[right] - 'a'] > 0) {
                cnt--;
            }
            // 该字符已考虑，计数器减一
            counts[s2[right] - 'a']--;

            //什么情况cnt==0？s2中的子串包含了s1所有字符，但是，这个子串有可能比s1长，只有相等才是正确的。
            while (cnt == 0) {
                if (right - left + 1 == m) {
                    return true;
                }

                // 左指针对应的计数器加1，为什么要这样做？因为前面右指针前进时已经对每个字符进行了减一
                // 如果此时左指针计数器加1后大于0，表示之前被右指针减后为0，也就是说这是s1的字符，所以cnt++
                counts[s2[left] - 'a']++;
                if (counts[s2[left] - 'a'] > 0) {
                    cnt++;
                }

                left++;
            }
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
