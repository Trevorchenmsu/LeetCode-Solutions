//There are n persons on a social media website. You are given an integer array 
//ages where ages[i] is the age of the ith person. 
//
// A Person x will not send a friend request to a person y (x != y) if any of th
//e following conditions is true: 
//
// 
// age[y] <= 0.5 * age[x] + 7 
// age[y] > age[x] 
// age[y] > 100 && age[x] < 100 
// 
//
// Otherwise, x will send a friend request to y. 
//
// Note that if x sends a request to y, y will not necessarily send a request to
// x. Also, a person will not send a friend request to themself. 
//
// Return the total number of friend requests made. 
//
// 
// Example 1: 
//
// 
//Input: ages = [16,16]
//Output: 2
//Explanation: 2 people friend request each other.
// 
//
// Example 2: 
//
// 
//Input: ages = [16,17,18]
//Output: 2
//Explanation: Friend requests are made 17 -> 16, 18 -> 17.
// 
//
// Example 3: 
//
// 
//Input: ages = [20,30,100,110,120]
//Output: 3
//Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
// 
//
// 
// Constraints: 
//
// 
// n == ages.length 
// 1 <= n <= 2 * 104 
// 1 <= ages[i] <= 120 
// 
// Related Topics Array Two Pointers Binary Search Sorting 
// 👍 442 👎 889


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table + math
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        unordered_map<int, int> counts;
        for (const auto &age : ages) { // O(n)
            counts[age]++;
        }

        /*
         * 因为x和y只能从当前有效的age选取，所以直接遍历count就可以得到所有有效的age
         * 只要满足request条件，就能够互粉。为什么这里一次request就够了而不需要x和y交换再考虑能否互粉？
         * 因为我们是遍历所有的age，假如先考虑了(x,y)，当x一直遍历时，又会在counts中遍历到等于y的值，此时
         * 的y就是当前x，也就是说我们达到了(y,x)的情况，因为有第二层遍历，所以这个x也可以是所有age。因此，
         * 在遍历中我们只需要request一次就可考虑两种情况。当两种age不等时，互粉的个数就是各自age的个数相乘。
         * 当两种age相等时，我们得去除其自身的情况，例如2，2，2，2，每一个2只能跟另外3个2互粉，总共有4个2，
         * 所以总数是n*(n-1)=4*3=12.
         * */
        int res = 0;
        for (auto &age_x : counts) { // O(120^2)=O(1)
            for (auto &age_y : counts) {
                if (request(age_x.first, age_y.first)) {
                    if (age_x.first != age_y.first) {
                        res += age_x.second * age_y.second;
                    }
                    else {
                        res += age_x.second * (age_y.second - 1);
                    }
                }
            }
        }

        return res;
    }

private:
    bool request(int age_x, int age_y) {
        return !((age_y <= 0.5 * age_x + 7) || (age_y > age_x) || (age_y > 100 && age_x < 100));
    }
};


/*
 * solution 2: hash table + binary search
 * time: O(nlogn)
 * space: O(1)
 * */
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());
        int n = ages.size(), reqs = 0;

        for(int i = n - 1; i >= 0; i--) {
            int val = 0.5 * ages[i] + 7;
            int index = upper_bound(ages.begin(), ages.end(), val) - ages.begin();

            int c = 1, prev = i;
            while(i - 1 >= 0 && ages[i] == ages[i-1]) {
                c++;
                i--;
            }

            if(index >= prev) continue;
            reqs += (prev - index) * c;
        }
        return reqs;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
