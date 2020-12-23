class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        unordered_map<int, int> um;
        int ans = INT_MAX;

        um[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            um[sum] = i;
        }
        sum = 0;
        if (um.find(x) != um.end()) {
            ans = min(ans, um[x] + 1);
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            sum += nums[i];
            if (um.find(x - sum) != um.end()) {
                int cnt = (int)nums.size() - i + um[x - sum] + 1;
                if (cnt > nums.size()) continue;
                ans = min(ans, cnt);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

