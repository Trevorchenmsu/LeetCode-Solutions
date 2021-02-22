/*
solution: trie + backtrack
time: O(n*m*4*3^(K-1)), n is row, m is col, K is the length of the word
space: O(L), the total length of the letters in the dictionary
*/
class Solution {
public:
    struct TrieNode {
        bool isWord = false;
        string hasWord = "";
        unordered_map<char, TrieNode*> leaves;
    };
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        TrieNode* root = buildTrie(words);
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                backtrack(res, board, root, i, j);
            }
        }
        return res;
    }

private:
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void backtrack(vector<string> &res, vector<vector<char>> &board, TrieNode* root, int i, int j) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;
        char c = board[i][j];
        if (c == '#' || root->leaves.find(c) == root->leaves.end())
            return;
        root = root->leaves[c];
        if (root->isWord) {
            res.push_back(root->hasWord);
            root->isWord = false;
        }
        board[i][j] = '#';
        for (const auto& dir : dirs) {
            backtrack(res, board, root, i + dir[0], j + dir[1]);
        }
        board[i][j] = c;
    }
    
    TrieNode* buildTrie(vector<string> &words) {
        TrieNode* root = new TrieNode();
        for (const auto& word : words) {
            TrieNode* cur = root;
            for (const auto& ch : word) {
                if (cur->leaves.find(ch) == cur->leaves.end())
                    cur->leaves[ch] = new TrieNode();
                cur = cur->leaves[ch];
            }
            cur->isWord = true;
            cur->hasWord = word;
        }
        
        return root;
    }
};