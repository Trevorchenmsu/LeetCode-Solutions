//Design a data structure that supports adding new words and finding if a string
// matches any previously added string. 
//
// Implement the WordDictionary class: 
//
// 
// WordDictionary() Initializes the object. 
// void addWord(word) Adds word to the data structure, it can be matched later. 
//
// bool search(word) Returns true if there is any string in the data structure t
//hat matches word or false otherwise. word may contain dots '.' where dots can be
// matched with any letter. 
// 
//
// 
// Example: 
//
// 
//Input
//["WordDictionary","addWord","addWord","addWord","search","search","search","se
//arch"]
//[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
//Output
//[null,null,null,null,false,true,true,true]
//
//Explanation
//WordDictionary wordDictionary = new WordDictionary();
//wordDictionary.addWord("bad");
//wordDictionary.addWord("dad");
//wordDictionary.addWord("mad");
//wordDictionary.search("pad"); // return False
//wordDictionary.search("bad"); // return True
//wordDictionary.search(".ad"); // return True
//wordDictionary.search("b.."); // return True
// 
//
// 
// Constraints: 
//
// 
// 1 <= word.length <= 25 
// word in addWord consists of lowercase English letters. 
// word in search consist of '.' or lowercase English letters. 
// There will be at most 3 dots in word for search queries. 
// At most 104 calls will be made to addWord and search. 
// 
// Related Topics String Depth-First Search Design Trie 
// 👍 5099 👎 247


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 0: trie+dfs, TLE
 * time: O(n) for addWord(), O(26*26*26*L) for search
 * space: O(L)
 * */
class TrieNode {
public:
    bool hasWord;
    unordered_map<char, TrieNode*> children;
    TrieNode(){
        hasWord = false;
    }
};

class WordDictionary {
private:
    TrieNode* root;
public:

    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* node = root;
        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->hasWord = true;
    }

    bool search(string word) {
        return helper(word, root);
    }

    bool helper(string word, TrieNode* node)
    {
        for (int i = 0; i < word.size(); ++i)
        {
            if (word[i] == '.')
            {
                for (auto &letter_child : node->children)
                {
                    if (helper(word.substr(i+1), letter_child.second)) return true;
                }
                return false;
            }
            else {
                auto it = node->children.find(word[i]);
                if (it == node->children.end()) return false;
                node = node->children[word[i]];
            }
        }

        return node->hasWord;
    }
};



/*
 * solution 1: trie+dfs, TLE
 * time: O(n) for addWord(), O(26*26*26*L) for search
 * space: O(L)
 * */
class TrieNode {
public:
    bool hasWord;
    unordered_map<char, TrieNode*> children;
    TrieNode(){
        hasWord = false;
    }
};

class WordDictionary {
private:
    TrieNode* root;
public:

    WordDictionary() {
        root = new TrieNode();
        root->hasWord = true;
    }

    void addWord(string word) {
        TrieNode* node = root;
        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->hasWord = true;
    }

    bool search(string word) {
        return find(word, root, 0);
    }

    bool find(string word, TrieNode* node, int idx)
    {
        if (idx == word.size()) return node->hasWord;

        auto it = node->children.find(word[idx]);
        if (it != node->children.end())
        {
            return find(word, node->children[word[idx]], idx + 1);
        }
        else if (word[idx] == '.')
        {
            for (const auto &letter_child : node->children)
            {
                if (find(word, letter_child.second, idx + 1))
                    return true;
            }
        }

        return false;
    }
};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
//leetcode submit region end(Prohibit modification and deletion)
