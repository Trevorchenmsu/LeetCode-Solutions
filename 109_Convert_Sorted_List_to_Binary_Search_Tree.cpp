/*
solution 1: recursion
time: O(nlogn), find the middle we use O(n) or O(n/2), for each part we use binary search which is O(logn)
so total is (nlogn)
space: O(logn), the maximum we would store is the total tree height, which is logn.
*/
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        return toBST(head, NULL);
    }
    
private:
    TreeNode* toBST(ListNode* head, ListNode* tail) {
        if (head == tail) return NULL;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != tail && fast->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }        
        TreeNode* node = new TreeNode(slow->val);
        node->left = toBST(head, slow);
        node->right = toBST(slow->next, tail);
        return node;
    }
};

/*
solution 2: convert list to array
time: O(n), find the middle we use O(n) or O(n/2), Accessing the middle element now takes O(1)O time 
and hence the time complexity comes down.
space: O(n), use the vector to store all the nodes
*/
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        vector<int> nums;
        while (head) {
            nums.push_back(head->val);
            head = head->next;
        }
        return helper(nums, 0, nums.size() - 1);
    }
    
private:
    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) return NULL;
        int mid = left + (right - left) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = helper(nums, left, mid - 1);
        node->right = helper(nums, mid + 1, right);
        return node;
    }
};