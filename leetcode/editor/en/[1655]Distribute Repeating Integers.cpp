//You are given an array of n integers, nums, where there are at most 50 unique 
//values in the array. You are also given an array of m customer order quantities,
// quantity, where quantity[i] is the amount of integers the ith customer ordered.
// Determine if it is possible to distribute nums such that: 
//
// 
// The ith customer gets exactly quantity[i] integers, 
// The integers the ith customer gets are all equal, and 
// Every customer is satisfied. 
// 
//
// Return true if it is possible to distribute nums according to the above condi
//tions. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3,4], quantity = [2]
//Output: false
//Explanation: The 0th customer cannot be given two different integers.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,3], quantity = [2]
//Output: true
//Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
//
// 
//
// Example 3: 
//
// 
//Input: nums = [1,1,2,2], quantity = [2,2]
//Output: true
//Explanation: The 0th customer is given [1,1], and the 1st customer is given [2
//,2].
// 
//
// Example 4: 
//
// 
//Input: nums = [1,1,2,3], quantity = [2,2]
//Output: false
//Explanation: Although the 0th customer could be given [1,1], the 1st customer 
//cannot be satisfied. 
//
// Example 5: 
//
// 
//Input: nums = [1,1,1,1,1], quantity = [2,3]
//Output: true
//Explanation: The 0th customer is given [1,1], and the 1st customer is given [1
//,1,1].
// 
//
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 105 
// 1 <= nums[i] <= 1000 
// m == quantity.length 
// 1 <= m <= 10 
// 1 <= quantity[i] <= 105 
// There are at most 50 unique values in nums. 
// 
// Related Topics Dynamic Programming Backtracking 
// 👍 128 👎 12


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        map<int,int> mark;
        vector<int> val;
        int vis[1050];
        int val_sum[1050];

        memset(vis,0,sizeof(vis));
        for(int i=0;i<nums.size();i++)mark[nums[i]]++;
        for(map<int,int>::iterator it = mark.begin();it!=mark.end();it++){
            val.push_back(it->second);
        }
        for(int l=1;l<(1<<quantity.size());l++){
            int sum=0;
            for(int k=0;k<quantity.size();k++){
                if(l&(1<<k)){
                    sum+=quantity[k];
                }
            }
            val_sum[l]=sum;
        }
        vis[0]=1;
        for(int i=0;i<val.size();i++){
            for(int j=(1<<quantity.size())-1;j>=0;j--){
                if(!vis[j])continue;
                for(int l=1;l<(1<<quantity.size());l++){
                    if(val[i]>=val_sum[l]){
                        vis[j|l]=1;
                    }
                }
            }
            if(vis[(1<<quantity.size())-1])return true;
        }
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
