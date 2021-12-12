//In an alien language, surprisingly they also use english lowercase letters, bu
//t possibly in a different order. The order of the alphabet is some permutation o
//f lowercase letters. 
//
// Given a sequence of words written in the alien language, and the order of the
// alphabet, return true if and only if the given words are sorted lexicographical
//y in this alien language. 
// 
// Example 1: 
//
// 
//Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
//Output: true
//Explanation: As 'h' comes before 'l' in this language, then the sequence is so
//rted.
// 
//
// Example 2: 
//
// 
//Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
//Output: false
//Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1]
//, hence the sequence is unsorted.
// 
//
// Example 3: 
//
// 
//Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
//Output: false
//Explanation: The first three characters "app" match, and the second string is 
//shorter (in size.) According to lexicographical rules "apple" > "app", because '
//l' > '∅', where '∅' is defined as the blank character which is less than any oth
//er character (More info).
// 
//
// 
// Constraints: 
//
// 
// 1 <= words.length <= 100 
// 1 <= words[i].length <= 20 
// order.length == 26 
// All characters in words[i] and order are English lowercase letters. 
// 
// Related Topics Array Hash Table String 
// 👍 2010 👎 769


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution: hash table
 * time: O(mn)
 * space: O(1)
 * */
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        if (words.empty()) return false;

        unordered_map<char, int> dict;

        for (int i = 0; i < order.size(); i++) {
            dict[order[i]] = i;
        }

        for (int i = 1; i < words.size(); i++) {
            string word1 = words[i - 1], word2 = words[i];
            int n1 = word1.size(), n2 = word2.size();

            for (int j = 0; j < n1 && j < n2; j++) {
                if (word1[j] == word2[j]) continue; // equal
                if (dict[word1[j]] > dict[word2[j]]) return false; // large than
                else break;
            }

            // smaller than
            if (n1 > n2 && word1.substr(0, n2) == word2) return false;
        }

        return true;
    }
}



//leetcode submit region end(Prohibit modification and deletion)
