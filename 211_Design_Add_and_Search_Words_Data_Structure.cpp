/*
solution 1: trie + dfs
time: addWord: O(n) 
      search: O(N*26^M), M is the word length, N is the number of words in the trie
      N is number of keys(keys = number of words we have in the Trie). 
      each key could have 26 chars and for M length of searched word, we need to search 26^M. 
      with all keys -> N*26^M
space: addWord: O(n) ; 
       search: O(logL)- stack space for dfs, L is the length of longest word
*/
class WordDictionary {
public:
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool isWord = false;
    };
    
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
        root->isWord = true;
    }
    
    void addWord(string word) {
        TrieNode* cur = root;
        for (const auto& c : word) {
            if (cur->leaves.find(c) == cur->leaves.end())
                cur->leaves[c] = new TrieNode();
            cur = cur->leaves[c];
        }
        cur->isWord = true;
    }
    
    bool search(string word) {
       return dfs(word, root, 0);
    }
    
private:
    TrieNode* root;
    bool dfs(string &s, TrieNode* node, int idx) {
        if (idx == s.size())
            return node->isWord;
        
        if (node->leaves.find(s[idx]) != node->leaves.end())
            return dfs(s, node->leaves[s[idx]], idx + 1);
        else if (s[idx] == '.') {
            for (const auto& leave : node->leaves) {
                if (dfs(s, leave.second, idx + 1))
                    return true;
            }
        }
            
        return false;
    }
    
};

/*
solution 2:hashtable
time: O(mn), m is the length of the word to find, n is the number of words
space: O(mn)
*/

class WordDictionary {
public:
    /** Initialize your data structure here. */
    unordered_map<int,vector<string>> m;
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        m[word.size()].push_back(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        for(auto str : m[word.size()])
        {
            int i = 0;
            while(i < word.size() && (str[i] == word[i] || word[i] == '.'))
            {
                i++;
            }
            if(i == word.size()) return true;
        }
        return false;
    }
};
