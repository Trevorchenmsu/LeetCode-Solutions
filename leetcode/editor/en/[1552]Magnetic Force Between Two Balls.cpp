//In universe Earth C-137, Rick discovered a special form of magnetic force betw
//een two balls if they are put in his new invented basket. Rick has n empty baske
//ts, the ith basket is at position[i], Morty has m balls and needs to distribute 
//the balls into the baskets such that the minimum magnetic force between any two 
//balls is maximum. 
//
// Rick stated that magnetic force between two different balls at positions x an
//d y is |x - y|. 
//
// Given the integer array position and the integer m. Return the required force
//. 
//
// 
// Example 1: 
//
// 
//Input: position = [1,2,3,4,7], m = 3
//Output: 3
//Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the ma
//gnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We c
//annot achieve a larger minimum magnetic force than 3.
// 
//
// Example 2: 
//
// 
//Input: position = [5,4,3,2,1,1000000000], m = 2
//Output: 999999999
//Explanation: We can use baskets 1 and 1000000000.
// 
//
// 
// Constraints: 
//
// 
// n == position.length 
// 2 <= n <= 10^5 
// 1 <= position[i] <= 10^9 
// All integers in position are distinct. 
// 2 <= m <= position.length 
// 
// Related Topics Array Binary Search 
// 👍 564 👎 59


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxDistance(vector<int>& position, int m)
    {
        sort(position.begin(), position.end());
        int left = 1, right = position.back()-position[0];
        while (left<right)
        {
            int mid = right-(right-left)/2;
            if (isOK(position, mid, m))
                left = mid;
            else
                right = mid-1;
        }
        return left;
    }

    bool isOK(vector<int>& position, int len, int m)
    {
        int j=0;
        int count = 1;

        for (int i=0; i<position.size(); )
        {
            j = i;
            while (j<position.size() && position[j]-position[i]<len)
                j++;

            if (j==position.size())
                break;
            else
            {
                count++;
                i=j;
            }
            if (count==m) return true;

        }
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
