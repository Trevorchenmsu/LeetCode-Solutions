/*
solution: trie + dfs
time: O(n*m*3^K), n is row, m is col, K is the length of the word
space: O(L), the total length of the letters in the dictionary

*/

struct TrieNode{
    bool isWord = false;
    unordered_map<char, TrieNode*> leaves;
    string hasWord = "";
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        root = buildTrie(words);
        for(int i = 0; i < board.size(); ++i){
            for(int j = 0; j < board[0].size(); ++j){
                dfs(board, i, j, root, res);
            }
        }
        return res;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* p, vector<string>& res){
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
        char c = board[i][j];
        if(c == '#' || !p->leaves.count(c)) return;
        p = p->leaves[c];
        if(p->isWord){
            res.push_back(p->hasWord);
            p->isWord = false;
        }
        board[i][j] = '#';
        dfs(board, i - 1, j, p, res);
        dfs(board, i + 1, j, p, res);
        dfs(board, i, j + 1, p, res);
        dfs(board, i, j - 1, p, res);
        board[i][j] = c;
    }
    
    TrieNode* buildTrie(vector<string>& words){
        TrieNode* root_ = new TrieNode();
        for(const auto& word : words){
            TrieNode* cur = root_;
            for (const auto& ch : word){
                if(cur->leaves.find(ch) == cur->leaves.end()){
                    cur->leaves[ch] = new TrieNode();
                }
                cur = cur->leaves[ch];
            }
            cur->isWord = true;
            cur->hasWord = word;
        }
        return root_;
    }
    
private: 
    TrieNode* root;
};