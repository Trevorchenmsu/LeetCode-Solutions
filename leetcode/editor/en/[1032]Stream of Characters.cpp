//Design an algorithm that accepts a stream of characters and checks if a suffix
// of these characters is a string of a given array of strings words. 
//
// For example, if words = ["abc", "xyz"] and the stream added the four characte
//rs (one by one) 'a', 'x', 'y', and 'z', your algorithm should detect that the su
//ffix "xyz" of the characters "axyz" matches "xyz" from words. 
//
// Implement the StreamChecker class: 
//
// 
// StreamChecker(String[] words) Initializes the object with the strings array w
//ords. 
// boolean query(char letter) Accepts a new character from the stream and return
//s true if any non-empty suffix from the stream forms a word that is in words. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["StreamChecker", "query", "query", "query", "query", "query", "query", "query
//", "query", "query", "query", "query", "query"]
//[[["cd", "f", "kl"]], ["a"], ["b"], ["c"], ["d"], ["e"], ["f"], ["g"], ["h"], 
//["i"], ["j"], ["k"], ["l"]]
//Output
//[null, false, false, false, true, false, true, false, false, false, false, fal
//se, true]
//
//Explanation
//StreamChecker streamChecker = new StreamChecker(["cd", "f", "kl"]);
//streamChecker.query("a"); // return False
//streamChecker.query("b"); // return False
//streamChecker.query("c"); // return False
//streamChecker.query("d"); // return True, because 'cd' is in the wordlist
//streamChecker.query("e"); // return False
//streamChecker.query("f"); // return True, because 'f' is in the wordlist
//streamChecker.query("g"); // return False
//streamChecker.query("h"); // return False
//streamChecker.query("i"); // return False
//streamChecker.query("j"); // return False
//streamChecker.query("k"); // return False
//streamChecker.query("l"); // return True, because 'kl' is in the wordlist
// 
//
// 
// Constraints: 
//
// 
// 1 <= words.length <= 2000 
// 1 <= words[i].length <= 2000 
// words[i] consists of lowercase English letters. 
// letter is a lowercase English letter. 
// At most 4 * 104 calls will be made to query. 
// 
// Related Topics Array String Design Trie Data Stream 
// 👍 918 👎 131


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash set, TLE
 * time: O(n*L)
 * space: O(n)
 * */
class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        for (const auto& w : words) {
            word_set.insert(w);
        }
        word = "";
    }

    bool query(char letter) {
        word.push_back(letter);
        int n = word.size();
        for (int i = 0; i < n; i++) {
            string word_sub = word.substr(i, n - i);
            auto iter = word_set.find(word_sub);
            if (iter != word_set.end()) {
                return true;
            }
        }

        return false;
    }

    unordered_set<string> word_set;
    string word;
};

/*
 * solution 2: Trie, TLE
 * time: O(n*L)
 * space: O(n)
 * */

class TrieNode{
public:
    bool isWord;
    string word;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isWord = false;
        word = "";
    }
};

class Trie{
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;

        for (const auto& ch : word) {
            auto it = node->children.find(ch);
            if (it == node->children.end()) {
                TrieNode* node_new = new TrieNode();
                node->children[ch] = node_new;
            }
            node = node->children[ch];
        }

        node->isWord = true;
        node->word = word;
    }

    bool hasWord(string word) {
        TrieNode* node = root;

        for (const auto& ch : word) {
            auto it = node->children.find(ch);
            if (it == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }

        return node->isWord;
    }

};

class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        trie = new Trie();
        for (const auto& w : words) {
            trie->insert(w);
        }
        word = "";
    }

    bool query(char letter) {
        word.push_back(letter);
        int n = word.size();
        for (int i = 0; i < n; i++) {
            string word_sub = word.substr(i, n - i);
            if (trie->hasWord(word_sub)) {
                return true;
            }
        }

        return false;
    }

    unordered_set<string> word_set;
    string word;
    Trie* trie;
};


/*
 * solution 3: Trie, pass
 * time: O(n)
 * space: O(n)
 * */

class TrieNode{
public:
    bool isWord;
    string word;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isWord = false;
        word = "";
    }
};

class Trie{
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        // 从单词尾部到头部开始建立字典树，目的是为了对应query那里从新加单词的尾部开始遍历
        for (int i = word.size() - 1; i >= 0; i--) {
            char ch = word[i];
            auto it = node->children.find(ch);
            if (it == node->children.end()) {
                TrieNode* node_new = new TrieNode();
                node->children[ch] = node_new;
            }
            node = node->children[ch];
        }

        node->isWord = true;
        node->word = word;
    }

};


class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        trie = new Trie();
        for (const auto& w : words) {
            trie->insert(w);
        }
        word = "";
    }

    bool query(char letter) {
        word.push_back(letter);
        int n = word.size();
        TrieNode* node = trie->root;
        for (int i = n - 1; i >= 0 && node; i--) {
            node = node->children[word[i]];
            if (node && node->isWord) {
                return true;
            }
        }

        return false;
    }

    unordered_set<string> word_set;
    string word;
    Trie* trie;
};
/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
//leetcode submit region end(Prohibit modification and deletion)
