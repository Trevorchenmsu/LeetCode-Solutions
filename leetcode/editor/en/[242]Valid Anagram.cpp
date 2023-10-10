//Given two strings s and t, return true if t is an anagram of s, and false othe
//rwise. 
//
// An Anagram is a word or phrase formed by rearranging the letters of a differe
//nt word or phrase, typically using all the original letters exactly once. 
//
// 
// Example 1: 
// Input: s = "anagram", t = "nagaram"
//Output: true
// Example 2: 
// Input: s = "rat", t = "car"
//Output: false
// 
// 
// Constraints: 
//
// 
// 1 <= s.length, t.length <= 5 * 104 
// s and t consist of lowercase English letters. 
// 
//
// 
// Follow up: What if the inputs contain Unicode characters? How would you adapt
// your solution to such a case? 
// Related Topics Hash Table String Sorting 
// 👍 10723 👎 335


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> s_map, t_map;

        for (const auto&ch : s)
            s_map[ch]++;

        for (const auto&ch : t)
            t_map[ch]++;

        if (s_map.size() != t_map.size())
            return false;

        for (const auto&k_v : s_map) {
            auto iter = t_map.find(k_v.first);
            if (iter == t_map.end())
                return false;
            else if (k_v.second != iter->second)
                return false;
        }

        return true;
    }
};

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;

        unordered_map<char, int> s_map, t_map;
        int len = s.length();
        for (int i = 0; i < len; ++i) {
            s_map[s[i]]++;
            t_map[t[i]]++;
        }

        for (const auto&k_v : s_map) {
            auto iter = t_map.find(k_v.first);
            if (iter == t_map.end())
                return false;
            else if (k_v.second != iter->second)
                return false;
        }

        return true;
    }
};

/*
 * solution 2: bucket
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length())
            return false;

        vector<int> count(26);
        for(int i = 0; i < s.length(); i++){
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for(int num : count){
            if(num != 0)
                return false;
        }

        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
