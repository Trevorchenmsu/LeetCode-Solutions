//Given an array of strings strs, group the anagrams together. You can return th
//e answer in any order. 
//
// An Anagram is a word or phrase formed by rearranging the letters of a differe
//nt word or phrase, typically using all the original letters exactly once. 
//
// 
// Example 1: 
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
// Example 2: 
// Input: strs = [""]
//Output: [[""]]
// Example 3: 
// Input: strs = ["a"]
//Output: [["a"]]
// 
// 
// Constraints: 
//
// 
// 1 <= strs.length <= 104 
// 0 <= strs[i].length <= 100 
// strs[i] consists of lower-case English letters. 
// 
// Related Topics Hash Table String Sorting 
// 👍 6291 👎 250


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table + sorting
 * time: O(nLlogL) = O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.empty() || strs.size() == 0) {
            return res;
        }

        unordered_map<string, vector<string>> ana2str;

        for (auto & str : strs) { //O(nLlogL)
            string ana = str;
            sort(ana.begin(), ana.end());
            ana2str[ana].push_back(str);
        }

        for (const auto&[ana, str] : ana2str) { // O(n)
            res.push_back(str);
        }

        return res;
    }
};

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        ana_dict = defaultdict(list)

        for word in strs:
            key = tuple(sorted(word))
            ana_dict[key].append(word)

        return list(ana_dict.values())
//leetcode submit region end(Prohibit modification and deletion)
