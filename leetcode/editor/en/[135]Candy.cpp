//There are n children standing in a line. Each child is assigned a rating value
// given in the integer array ratings. 
//
// You are giving candies to these children subjected to the following requireme
//nts: 
//
// 
// Each child must have at least one candy. 
// Children with a higher rating get more candies than their neighbors. 
// 
//
// Return the minimum number of candies you need to have to distribute the candi
//es to the children. 
//
// 
// Example 1: 
//
// 
//Input: ratings = [1,0,2]
//Output: 5
//Explanation: You can allocate to the first, second and third child with 2, 1, 
//2 candies respectively.
// 
//
// Example 2: 
//
// 
//Input: ratings = [1,2,2]
//Output: 4
//Explanation: You can allocate to the first, second and third child with 1, 2, 
//1 candies respectively.
//The third child gets 1 candy because it satisfies the above two conditions.
// 
//
// 
// Constraints: 
//
// 
// n == ratings.length 
// 1 <= n <= 2 * 104 
// 0 <= ratings[i] <= 2 * 104 
// 
// Related Topics Array Greedy 
// 👍 2122 👎 222


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: mini heap + hash table
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.empty() || ratings.size() == 0) {
            return 0;
        }

        unordered_map<int, int> cnts;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for (int i = 0; i < ratings.size(); i++) { // O(nlogn)
            cnts[i] = 1;
            pq.push({ratings[i], i});
        }


        while (!pq.empty()) { // O(nlogn)
            auto cur = pq.top(); pq.pop();
            int rate = cur[0], idx = cur[1];

            if (idx - 1 >= 0 && rate > ratings[idx - 1]) {
                cnts[idx] = max(cnts[idx], cnts[idx - 1] + 1);
            }

            if (idx + 1 < ratings.size() && rate > ratings[idx + 1]) {
                cnts[idx] = max(cnts[idx], cnts[idx + 1] + 1);
            }
        }

        int res = 0;
        for (auto &[idx, cnt] : cnts) { // O(n)
            res += cnt;
        }

        return res;

    }
};

/*
 * solution 2: greedy
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int candy(vector<int>& ratings) {
        int res = 0;
        if (ratings.empty() || ratings.size() == 0) {
            return res;
        }

        int n = ratings.size();
        vector<int> cnts (n, 1);

        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                cnts[i] = cnts[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                cnts[i] = max(cnts[i], cnts[i + 1] + 1);
            }
        }

        int sum = accumulate(cnts.begin(), cnts.end(), 0);
        return sum;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
