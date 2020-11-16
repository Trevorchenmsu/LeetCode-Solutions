/*
solution: hashtable + backtracking
time: O(n!)
space：O(n)
*/
class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        int res = INT_MAX;
        
        // get the money map. x gives y &z
        unordered_map<int, int> map;
        for (auto t : transactions) {
            map[t[0]] -= t[2];
            map[t[1]] += t[2];
        }
        
        // get the unbalanced money
        vector<int> account;
        for (auto m : map) {
            if (m.second != 0) account.push_back(m.second);
        }
                
        helper(res, account, 0, 0);
        return res;
    }

private:
    void helper(int& res, vector<int>& account, int start, int cnt) {
        int n = account.size();
        while (start < n && account[start] == 0) ++start;
        if (start == n) {
            res = min(res, cnt);
            return;
        }
        for (int i = start + 1; i < n; ++i) {
            if ((account[i] < 0 && account[start] > 0) || (account[i] > 0 && account[start] < 0)) {
                account[i] += account[start];
                helper(res, account, start + 1, cnt + 1);
                account[i] -= account[start];
            }
        }
    }
};