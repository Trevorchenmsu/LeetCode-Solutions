//A trie (pronounced as "try") or prefix tree is a tree data structure used to e
//fficiently store and retrieve keys in a dataset of strings. There are various ap
//plications of this data structure, such as autocomplete and spellchecker. 
//
// Implement the Trie class: 
//
// 
// Trie() Initializes the trie object. 
// void insert(String word) Inserts the string word into the trie. 
// boolean search(String word) Returns true if the string word is in the trie (i
//.e., was inserted before), and false otherwise. 
// boolean startsWith(String prefix) Returns true if there is a previously inser
//ted string word that has the prefix prefix, and false otherwise. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
//[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
//Output
//[null, null, true, false, true, null, true]
//
//Explanation
//Trie trie = new Trie();
//trie.insert("apple");
//trie.search("apple");   // return True
//trie.search("app");     // return False
//trie.startsWith("app"); // return True
//trie.insert("app");
//trie.search("app");     // return True
// 
//
// 
// Constraints: 
//
// 
// 1 <= word.length, prefix.length <= 2000 
// word and prefix consist only of lowercase English letters. 
// At most 3 * 104 calls in total will be made to insert, search, and startsWith
//. 
// 
// Related Topics Hash Table String Design Trie 
// 👍 7528 👎 95


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: trie/prefix tree
 * time: O(L), L is the length of word
 * space: O(L) for insert, O(1) for the rest
 * */

class TrieNode {
public:
    string word_;
    bool hasWord;
    unordered_map<char, TrieNode*> children;
    TrieNode() {
        word_ = "";
        hasWord = false;
    };
    TrieNode(string word): word_ (word), hasWord(false) {}
};


class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;

        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end())
            {
                TrieNode* node_new = new TrieNode();
                node->children[ch] = node_new;
            }
            node = node->children[ch];
        }

        node->word_ = word;
        node->hasWord = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end()) return false;
            node = node->children[ch];
        }

        return node->hasWord;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (auto ch : prefix)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end()) return false;
            node = node->children[ch];
        }

        return true;
    }
};
class TrieNode:
    def __init__(self):
        self.word = ''
        self.hasWord = False
        self.children = {}

class Trie:

    def __init__(self):
     self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children.keys():
                node_new = TrieNode()
                node.children[ch] = node_new
            node = node.children[ch]

        node.word = word;
        node.hasWord = True


    def search(self, word: str) -> bool:
        node = self.root
        for ch in word:
            if ch not in node.children.keys():
                return False
        node = node.children[ch]

        return node.hasWord

    def startsWith(self, prefix: str) -> bool:
        node = self.root
        for ch in prefix:
            if ch not in node.children.keys():
                return False
        node = node.children[ch]
        return True
/*
 * solution 2: same as solution 1, simpler
 * */

class TrieNode {
public:
    string word_;
    bool hasWord;
    unordered_map<char, TrieNode*> children;
    TrieNode() {
        word_ = "";
        hasWord = false;
    };
    TrieNode(string word): word_ (word), hasWord(false) {}
};


class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;

        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end())
            {
                TrieNode* node_new = new TrieNode();
                node->children[ch] = node_new;
            }
            node = node->children[ch];
        }

        node->word_ = word;
        node->hasWord = true;
    }

    bool search(string word) {
        TrieNode* node = childSearch(word);

        return node ? node->hasWord : false ;
    }

    bool startsWith(string prefix) {
        return childSearch(prefix);
    }

    TrieNode* childSearch(string &word){
        TrieNode* node = root;
        for (auto ch : word)
        {
            auto it = node->children.find(ch);
            if (it == node->children.end()) return nullptr;
            node = node->children[ch];
        }

        return node;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
//leetcode submit region end(Prohibit modification and deletion)
