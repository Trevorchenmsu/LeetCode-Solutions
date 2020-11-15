/*
solution: trie
time:
space:
*/
struct TrieNode{
    bool isWord = false;
    unordered_map<char, TrieNode*> leaves;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
        root->isWord = true;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        auto* cur = root;
        for(const auto& ch : word){
            if(!cur->leaves.count(ch)){
                cur->leaves[ch] = new TrieNode();
            }
            cur = cur->leaves[ch];
        }
        cur->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto* node =  childSearch(word);
        return node ? node->isWord : false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return childSearch(prefix);
    }
    
    TrieNode* childSearch(string word){
        auto* cur = root;
        for(const auto& ch : word){
            if(cur->leaves.count(ch)){
                cur = cur->leaves[ch];
            } else 
                return NULL;
        }
        return cur;
    }
    
private:
    TrieNode* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */