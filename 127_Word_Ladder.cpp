/*
solution： BFS
time: O(26*M×N), where M is the length of each word and N is the total number of words in the input word list.
For each word in the word list, we iterate over its length to find all the intermediate words corresponding to it. 
Since the length of each word is M and we have N words, 
the total number of iterations the algorithm takes to create 
all_combo_dict is M×N. Additionally, forming each of the intermediate word takes O(M) time 
because of the substring operation 
used to create the new string. This adds up to a complexity of O(M^2×N).

Breadth first search in the worst case might go to each of the N words. For each word, we need to examine 
M possible intermediate words/combinations. Notice, we have used the substring operation to find each of the combination. 
Thus, M combinations take O(M^2) time. As a result, the time complexity of BFS traversal would also be O(M^2×N).
Combining the above steps, the overall time complexity of this approach is O(M^2×N).

space: O(26*M×N).
Each word in the word list would have M intermediate combinations. To create the all_combo_dict 
dictionary we save an intermediate word as the key and its corresponding original words as the value. 
Note, for each of M intermediate words we save the original word of length M. This simply means, 
for every word we would need a space of M^2 to save all the transformations corresponding to it. 
Thus, all_combo_dict would need a total space of O(M^2×N).
Visited dictionary would need a space of O(M×N) as each word is of length M.
Queue for BFS in worst case would need a space for all O(N) words and this would also result 
in a space complexity of O(M×N). Combining the above steps, the overall space complexity is O(M^2×N)+O(M∗N)+O(M∗N)=O(M^2×N) 
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // convert the vector to set, in order to reduce duplicate words
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // edge case
        if (wordList.empty() || wordList.size() == 0) 
            return -1;
        
        // if the endword does not exist or the beginword is the same as end word
        if (!wordSet.count(endWord))
            return 0;
        if (beginWord == endWord)
            return 1;
        
        // BFS
        queue<string> q;
        q.push(beginWord);
        wordSet.erase(beginWord); // as we already consider the beginword
        int level = 2; // as we already consider 0 and 1 cases
        
        while(!q.empty()) {
            // traverse for different levels
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string word = q.front(); q.pop();
                // consider each character in the word
                for (int j = 0; j < word.size(); ++j) {
                    // store inital word
                    char oldChar = word[j];
                    // consider 26 characters 
                    for (char c = 'a'; c <= 'z'; ++c){
                        if (c == word[j]) {
                            continue;
                        }
                        // get the new word which is the neighbor
                        word[j] = c;
                        if (word == endWord) 
                            return level;
                        if (wordSet.count(word)) {
                            q.push(word); // as this exists in the set, we need to add it for next consideration
                            wordSet.erase(word); // as we already consider the word, it is no longer useful.
                        }                                       
                    }
                    // return back the intial word.
                    word[j] = oldChar;
                }
                
            }
            ++level;
        }
        
        return 0;
    }
};