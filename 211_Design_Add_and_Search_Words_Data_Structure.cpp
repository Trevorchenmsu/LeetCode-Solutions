/*
solution 1: trie
time:
space:
*/

struct TrieNode{
    bool isWord = false;
    unordered_map<char, TrieNode*> leaves;
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
        root->isWord = true;
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        auto* p = root;
        for (const auto& c : word) {
            if (p->leaves.find(c) == p->leaves.end()) {
                p->leaves[c] = new TrieNode;
            }
            p = p->leaves[c];
        }
        p->isWord = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return find(word, root, 0);
    }
    
    bool find(string word, TrieNode* node, int idx){
        // recursion exit
        if(idx == word.size()) 
            return node->isWord;
        
        if(node->leaves.find(word[idx]) != node->leaves.end()){
            return find(word, node->leaves[word[idx]], idx + 1);
        } else if(word[idx] == '.'){
            for(const auto& leave : node->leaves){
                if(find(word, leave.second, idx + 1)){
                    return true;
                }
            }
        }
        
        return false;
    }

private:
    TrieNode* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

/*
solution 2:vector
time:
space:
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
