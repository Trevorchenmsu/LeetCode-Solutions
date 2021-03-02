/*
solution 1: bitwise Trie
time: O(N)
space: O(N), for each integer, we need 32 bits, we have N numbers, total is O(32N) = O(N)
*/

class Solution {
public:
    struct TrieNode {
        unordered_map<int, TrieNode*> leaves;    
    };
    
    int findMaximumXOR(vector<int>& nums) {
        int res = INT_MIN;
        TrieNode* root = buildTrie(nums); // O(n)
        for (const auto& num : nums) { // O(n)
            res = max(res, findMaxXOR(root, num));
        }
        return res;
    }

private:
    TrieNode* buildTrie(vector<int> &nums) {
        TrieNode* root = new TrieNode();
        for (const auto& num : nums) {
            TrieNode* cur = root;
            for (int i = 31; i >= 0; i--) {
                int numBit = (num >> i) & 1; // get each bit from integer
                if (cur->leaves.find(numBit) == cur->leaves.end()) {
                    cur->leaves[numBit] = new TrieNode();
                }
                cur = cur->leaves[numBit];
            }
        }
        return root;
    }
    
    int findMaxXOR(TrieNode* root, int num) {
        int sum = 0;
        TrieNode* cur = root;
        for (int i = 31; i >= 0; i--) {
            int numBit = (num >> i) & 1; 
            int otherChoice = numBit == 1 ? 0 : 1;
            if (cur->leaves.find(otherChoice) == cur->leaves.end()) {
                cur = cur->leaves[numBit];
            }
            else {
                sum += (1 << i);
                cur = cur->leaves[otherChoice];
            }
        }
        return sum;
    }
};