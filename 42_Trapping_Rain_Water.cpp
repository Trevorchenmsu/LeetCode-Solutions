/*
solution 1: brute force
time: O(n^2)
space: O(1)
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        for (int i = 1; i < height.size(); i++) {
            int left_max = 0, right_max = 0;
            for (int j = i ; j >= 0; j--) {
                left_max = max(left_max, height[j]);
            }
            
            for (int j = i; j < height.size(); j++) {
                right_max = max(right_max, height[j]);
            }
            res += min(left_max, right_max) - height[i];
        }
        return res;
    }
};

/*
solution 2: dp
time: O(n)
space: O(n)
*/
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int res = 0, n = height.size();
        
        // dp
        vector<int> left_max(n), right_max(n);
        left_max[0] = height[0];
        for (int i = 1; i < n; i++) {
            left_max[i] = max(height[i], left_max[i - 1]);
        }
        
        right_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            right_max[i] = max(height[i], right_max[i + 1]);
        }
        
        for (int i = 1; i < n; i++) {
            res += min(left_max[i], right_max[i]) - height[i];
        }
        
        return res;
    }
};

/*
solution 3: monotonomous stack
time: O(n)
space: O(n)
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, i = 0;
        stack<int> Stack;
        
        while (i < height.size()) {
            while (!Stack.empty() && height[i] > height[Stack.top()]) {
                int top = Stack.top();
                Stack.pop();
                if (Stack.empty()) break; // this step is necessary since the last element is not counted as volume.
                int width = i - Stack.top() - 1; // Stack.top() cannot be replaced by top
                int height_trap = min(height[i], height[Stack.top()]) - height[top];
                int area = width * height_trap;
                res += area;
            }
            Stack.push(i++);
        }
        
        return res;
    }
};

/*
solution 4: two pointers
time: O(n)
space: O(1)
*/

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