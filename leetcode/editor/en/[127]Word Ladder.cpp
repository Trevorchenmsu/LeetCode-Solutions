//A transformation sequence from word beginWord to word endWord using a dictiona
//ry wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
// 
//
// 
// Every adjacent pair of words differs by a single letter. 
// Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to
// be in wordList. 
// sk == endWord 
// 
//
// Given two words, beginWord and endWord, and a dictionary wordList, return the
// number of words in the shortest transformation sequence from beginWord to endWo
//rd, or 0 if no such sequence exists. 
//
// 
// Example 1: 
//
// 
//Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot"
//,"log","cog"]
//Output: 5
//Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -
//> "dog" -> cog", which is 5 words long.
// 
//
// Example 2: 
//
// 
//Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot"
//,"log"]
//Output: 0
//Explanation: The endWord "cog" is not in wordList, therefore there is no valid
// transformation sequence.
// 
//
// 
// Constraints: 
//
// 
// 1 <= beginWord.length <= 10 
// endWord.length == beginWord.length 
// 1 <= wordList.length <= 5000 
// wordList[i].length == beginWord.length 
// beginWord, endWord, and wordList[i] consist of lowercase English letters. 
// beginWord != endWord 
// All the words in wordList are unique. 
// 
// Related Topics Hash Table String Breadth-First Search 
// 👍 5417 👎 1454


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: BFS, slow version, not optimal
 * time: O(n*26*L^2), n is the number of words, L is the maximum length of the word
 * space: O(n*L)
 *
 * */
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end()); //O(n)

        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }

        if (beginWord == endWord) {
            return 1;
        }

        queue<string> q;
        q.push(beginWord);

        unordered_set<string> visited;
        visited.insert(beginWord);
        wordSet.insert(endWord);

        int step = 1;
        while (!q.empty()) {
            int len = q.size();
            while (len--) { //  O(n*26*L^3)
                string word_cur = q.front(); q.pop();
                if (word_cur == endWord) {
                    return step;
                }

                vector<string> words_neighbor = getNeighbors(word_cur);
                for (auto &word : words_neighbor) { // O(26*L*L)
                    if (wordSet.find(word) == wordSet.end() || visited.find(word) != visited.end()) { // O(L)
                        continue;
                    }

                    q.push(word);//O(L)
                    visited.insert(word); //O(L)
                }
            }
            step++;
        }

        return 0;
    }

private:
    vector<string> getNeighbors(string &s) { // O(26*L)
        vector<string> res;
        for (int i = 0; i < s.size(); i++) {
            char ch_old = s[i];
            for (char ch_new = 'a'; ch_new <= 'z'; ch_new++) {
                if (ch_new == ch_old) {
                    continue;
                }
                s[i] = ch_new;
                res.push_back(s);
            }
            s[i] = ch_old;
        }
        return res;
    }
};


/*
 * solution 2: BFS
 * time: O(n*26*L^2), n is the number of words, L is the maximum length of the word
 * space: O(n*L)
 *
 * */
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // convert the vector to set, in order to reduce duplicate words
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // edge case
        if (wordList.empty() || wordList.size() == 0)
            return -1;

        // if the endWord does not exist or the beginWord is the same as end word
        if (!wordSet.count(endWord))
            return 0;
        if (beginWord == endWord)
            return 1;

        // BFS
        queue<string> q;
        q.push(beginWord);
        wordSet.erase(beginWord); // as we already consider the beginWord
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
                    // return back the initial word.
                    word[j] = oldChar;
                }

            }
            ++level;
        }

        return 0;
    }
};


/*
 * solution 3: BFS, optimal
 * time: O(n*26*L^2), n is the number of words, L is the maximum length of the word
 * space: O(n*L)
 *
 * */
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end()); // O(n*L)

        if (beginWord == endWord) {
            return 1;
        }

        auto it = wordSet.find(endWord);
        if (it == wordSet.end()) {
            return 0;
        }

        wordSet.erase(beginWord);
        queue<string> q;
        q.push(beginWord);

        int step = 1;
        while (!q.empty()) {
            int len = q.size();
            while (len--) { // O(n)
                string word = q.front(); q.pop();
                if (word == endWord) {
                    return step;
                }

                for (int i = 0; i < word.size(); i++) { // O(26*L^2)
                    char ch = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == ch) {
                            continue;
                        }
                        word[i] = c;
                        auto it = wordSet.find(word);
                        if (it != wordSet.end()) {
                            q.push(word); // push() is push the copy of word to the queue, in string class it takes O(L)
                            wordSet.erase(word);
                        }
                    }
                    word[i] = ch;
                }
            }
            step++;
        }

        return 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
