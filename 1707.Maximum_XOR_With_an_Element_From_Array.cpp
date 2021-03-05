/*
solution 1: brute force, TLE
time: O(mn), m is the lenght of queries, n is the length of nums
space: O(1)
*/
class Solution {
public:  
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> res;

        for (const auto& query : queries) {
            int val = INT_MIN;

            for (const auto& num : nums) {
                if (num > query[1]) continue;
                val = max(val, num ^ query[0]);
            }

            val = val == INT_MIN ? -1 : val;
            res.push_back(val);
        }
        
        return res;
    }
};

//卡点：如果我用nums建立trie，是一个整个trie，但是对每个小于query[1]的有效元素，是一个nums的子数组，如何
// 避免query[0]跟子数组外的元素进行异或

struct TrieNode {
    int lo = INT_MAX;
    TrieNode* children[2]{};
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        for (auto q : queries) {
            int x = q[0], limit = q[1];
            int ans = 0;
            TrieNode* p = root;
            for (int i = 30; i >= 0; --i) {
                if (x & (1 << i)) {
                    if (p->children[0]) {
                        p = p->children[0];
                        ans ^= (1 << i);
                    } else if (!p->children[1] || (p->children[1]->lo > limit)) {
                        ret.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[1];
                    }
                } else {
                    if (p->children[1] && (p->children[1]->lo <= limit)) {
                        p = p->children[1];
                        ans ^= (1 << i);
                    } else if (!p->children[0]) {
                        ret.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[0];
                    }
                }
                if (i == 0) ret.emplace_back(ans);
            }
        }
        return ret;
    }
};
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




   class Solution {
public:
    struct TrieNode{
        unordered_map<int, TrieNode*> leaves;
        int lo = INT_MAX;
    };
    
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> res;
        TrieNode* root = buildTrie(nums);
        
        // for (auto& query : queries) {
        //     TrieNode* cur = root;
        //     findMaxXOR(query, cur, res);
        // }
        TrieNode* cur = root;
        findMaxXOR(queries[0], cur, res);
        
        return res;
    }
    
    TrieNode* buildTrie(vector<int> &nums) {
        TrieNode* root = new TrieNode();
        for (const auto& num : nums) {
            TrieNode* cur = root;
            for (int i = 31; i >= 0; i--) {
                int curBit = (num >> i) & 1;
                if (cur->leaves.find(curBit) == cur->leaves.end()) {
                    cur->leaves[curBit] = new TrieNode();
                }
                cur = cur->leaves[curBit];
                cur->lo = min(cur->lo, num);
            }
        }
        
        return root;
    }
    
    void findMaxXOR(vector<int> &query, TrieNode* cur, vector<int> &res) {
        int x = query[0], m = query[1], sum = 0;
        for (int i = 31; i >= 0; i--) {
            if (cur->lo > m) break; // 定义有问题
            int curBit = (x >> i) & 1; 
            int otherChoice = curBit == 1 ? 0 : 1;
            if (cur->leaves.find(otherChoice) == cur->leaves.end()) {
                cur = cur->leaves[curBit];
            }
            else {
                // if (cur->leaves[otherChoice]->lo > m) 
                //     cur = cur->leaves[curBit];
                // else {
                //     sum += (1 << i); 
                //     cur = cur->leaves[otherChoice];
                // }
                sum += (1 << i); 
                cur = cur->leaves[otherChoice];
            }
        }
        sum = sum == 0 ? -1 : sum;
        res.push_back(sum);
    }
};