//Given n non-negative integers representing an elevation map where the width of
// each bar is 1, compute how much water it can trap after raining. 
//
// 
// Example 1: 
//
// 
//Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
//Output: 6
//Explanation: The above elevation map (black section) is represented by array [
//0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are
// being trapped.
// 
//
// Example 2: 
//
// 
//Input: height = [4,2,0,3,2,5]
//Output: 9
// 
//
// 
// Constraints: 
//
// 
// n == height.length 
// 1 <= n <= 2 * 104 
// 0 <= height[i] <= 105 
// 
// Related Topics Array Two Pointers Dynamic Programming Stack Monotonic Stack 
// 👍 13264 👎 189


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force, TLE
 * time: O(n^2)
 * space: O(1)
 * */

/*
 * 为什么stuck？
 * 1.我想到的是当前元素的左右两边最大值互减得到高度差，而不是取较小值来减去当前高度得到高度差
 * 2.另一个误区:得到上面的高度差后，我以为得用左右两个高度的位置之差得到宽度，然后用宽度乘以高度差才得到容积，
 * 但实际上对于每个格子，从1中得到的高度差就可以表示当前位置的容积。
 * */
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        for (int i = 1; i < height.size(); i++) {
            int max_left = INT_MIN;
            for (int j = i; j >= 0; j--) {
                max_left = max(max_left, height[j]);
            }

            int max_right = INT_MIN;
            for (int j = i; j < height.size(); j++) {
                max_right = max(max_right, height[j]);
            }

            res += min(max_left, max_right) - height[i];
        }

        return res;
    }
};

/*
 * solution 2: dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty() || height.size() == 0) {
            return 0;
        }

        int res = 0, n = height.size();
        vector<int> max_heights_left (n);
        vector<int> max_heights_right (n);

        max_heights_left[0] = height[0];
        for (int i = 1; i < n; i++) {
            max_heights_left[i] = max(height[i], max_heights_left[i - 1]);
        }

        max_heights_right[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            max_heights_right[i] = max(height[i], max_heights_right[i + 1]);
        }


        for (int i = 1; i < height.size(); i++) {
            res += min(max_heights_left[i], max_heights_right[i]) - height[i];
        }

        return res;
    }
};

/*
 * solution 3: monotonic stack,单调递减栈
 * time: O(n)
 * space: O(n)
 *
 * */

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty() || height.size() == 0) {
            return 0;
        }

        int res = 0;
        stack<int> st;

        for (int i = 0; i < height.size(); i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int top = st.top(); st.pop();
                if (st.empty()) {
                    break;
                }

                int cur_height = min(height[st.top()], height[i]) - height[top];
                int cur_width = i - 1 - st.top();
                res += cur_height * cur_width;
            }
            st.push(i);
        }

        return res;
    }
};

/*
 * solution 4: two pointers, optimal
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int res = 0;
        int left_max = 0, right_max = 0;

        while (left < right) {
            if(height[left] < height[right]) {
                left_max = max(left_max, height[left]);
                res += left_max - height[left];
                left++;
            }
            else {
                right_max = max(right_max, height[right]);
                res += right_max - height[right];
                right--;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
