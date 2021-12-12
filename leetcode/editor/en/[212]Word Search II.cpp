//Given an m x n board of characters and a list of strings words, return all wor
//ds on the board. 
//
// Each word must be constructed from letters of sequentially adjacent cells, wh
//ere adjacent cells are horizontally or vertically neighboring. The same letter c
//ell may not be used more than once in a word. 
//
// 
// Example 1: 
//
// 
//Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f"
//,"l","v"]], words = ["oath","pea","eat","rain"]
//Output: ["eat","oath"]
// 
//
// Example 2: 
//
// 
//Input: board = [["a","b"],["c","d"]], words = ["abcb"]
//Output: []
// 
//
// 
// Constraints: 
//
// 
// m == board.length 
// n == board[i].length 
// 1 <= m, n <= 12 
// board[i][j] is a lowercase English letter. 
// 1 <= words.length <= 3 * 104 
// 1 <= words[i].length <= 10 
// words[i] consists of lowercase English letters. 
// All the strings of words are unique. 
// 
// Related Topics Array String Backtracking Trie Matrix 
// 👍 4336 👎 153


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: Trie + dfs
 * time: O(mn*4*3^L)
 * space: O(k*L)
 *
 * */
class TrieNode {
public:
    string word;
    bool isWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        word = "";
        isWord = false;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string &word) {
        TrieNode* node = root; // 因为要持续遍历root，为了不更改根节点，创建副节点
        for (auto &ch : word) {
            auto it = node->children.find(ch);
            if (it == node->children.end()) {
                TrieNode* node_new = new TrieNode();
                node->children[ch] = node_new;
            }
            node = node->children[ch];
        }

        node->word = word;
        node->isWord = true;
    }

    //这部分可删除，没用到，但是保留整体性，留着
    bool hasWord(string &word) {
        TrieNode* node = root;
        for (auto &ch : word) {
            auto it = node->children.find(ch);
            if (it == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }

        return true;
    }
};

class Solution {
public:
    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int m, n;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size(), n = board[0].size();

        // build segment tree
        Trie* trie = new Trie();
        buildTrie(trie, words);

        vector<string> res;
        // 以矩阵的每个字符为起点，搜索所有有效路径
        for (int i = 0; i < m; i++) { // O(m*n)
            for (int j = 0; j < n; j++) {
                search(board, i, j, res, trie->root->children[board[i][j]]); // O(4^L);
            }
        }

        return res;
    }

    void buildTrie(Trie* trie, vector<string> &words) {
        for (auto &word : words) { // O(k*L), k is the number of words
            trie->insert(word);
        }
    }

    void search(vector<vector<char>> &board, int x, int y, vector<string> &res, TrieNode* node) {
        if (node == NULL) {
            return;
        }

        if (node->isWord) {
            res.push_back(node->word);
            node->isWord = false; //去重
        }

        char letter = board[x][y];
        board[x][y] = '#';
        for (auto &dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }

            char c = board[nx][ny];
            auto it = node->children.find(c);
            if (c == '#' || it == node->children.end()) {
                continue;
            }

            search(board, nx, ny, res, node->children[c]);
        }

        board[x][y] = letter;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
