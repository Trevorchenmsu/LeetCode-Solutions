class Solution {
    public:
        vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
            map<int,int> mp;
            stack<int> stack;
    
            for(int value: nums1) {
                mp[value] = -1;
            }
            
            for(int i=0;i<nums2.size();i++) {
                while (!stack.empty()&&stack.top()<nums2[i]) {
                    mp[stack.top()] = nums2[i];
                    stack.pop();
                }
                stack.push(nums2[i]);
            }
            
            for(int i=0;i<nums1.size();i++) {
                nums1[i] = mp[nums1[i]];
            }
            return nums1;
        }
    };

