/*
solution: hashmap
time: O(mn), m is the size of the word array, n is the average length of the word in the array
space: O(L), L is the length of the dictionary to store the order
*/
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
};


