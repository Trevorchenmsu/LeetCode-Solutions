/*
solution 1: monotonic stack
time: O(n), traverse the height array
space: O(n), the worst case is all the heights monotonicall increase.
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty() || heights.size() == 0){
            return 0;
        }
        
        int res = INT_MIN;
        stack<int> s;
        for(int i = 0; i <= heights.size(); ++i){
            int curHeight = i == heights.size() ? -1 : heights[i];
            while(!s.empty() && curHeight < heights[s.top()]){
                cout << s.top() <<" "<< i<<" "<<endl;
                int height = heights[s.top()]; s.pop();
                int start = s.empty() ? -1 : s.top();
                int width = i - 1 - start;
                res = max(res, height * width);
            }
            s.push(i);
        }
        
        return res;
    }
};

/*
solution 2: monotonic stack
time: O(n), traverse the height array
space: O(n), the worst case is all the heights monotonicall increase.
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty() || heights.size() == 0){
            return 0;
        }
        
        int res = INT_MIN;
        heights.push_back(0); // to pop up all the element in monotonic stack
        vector<int> index;
        
        for(int i = 0; i < heights.size(); ++i){
            while(index.size() > 0 && heights[index.back()] >= heights[i]){
                int height = heights[index.back()];
                index.pop_back();
                int start = index.size() > 0 ? index.back() : -1;
                int width = i - 1 - start;
                res = max(res, height * width);
            }
            index.push_back(i);
        }
        return res;
    }
};

  
        