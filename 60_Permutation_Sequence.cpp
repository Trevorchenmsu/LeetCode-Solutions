/*
solution: factorial number system
time: O(n^2), traverse n - O(n), erase element in an array - O(n), total is O(n^2)
space: O(n)
*/
class Solution {
public:
    string getPermutation(int n, int k) {
        string res = "";
        vector<int> factorials (n);
        factorials[0] = 1;
        vector<int> nums (1, 1);
        
        // build number factorial and the number array
        for (int i = 1; i < n; i++) {
            factorials[i] = factorials[i - 1] * i;
            nums.push_back(i + 1);
        }
        
        // make k fit the factorial system
        k--;
        
        // use factorial number system
        for (int i = n - 1; i >= 0; i--) {
            int idx = k / factorials[i];
            k -= idx * factorials[i];
            res.push_back(nums[idx] + '0');
            nums.erase(nums.begin() + idx);
        }
        
        return res;
    }
};