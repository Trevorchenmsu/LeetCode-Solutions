/*
solution 1: divide and conquer + merge sort
time: O(nklogk), k is the number of the lists, n is the length of each list ? might be more for this method
space: O(logk), stack space  ? might be more for this method
*/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        if (lists.size() == 1) return lists[0];
        if (lists.size() == 2) return mergeSort(lists[0], lists[1]);
        
        // divide and conquer + merge sort
        int mid = lists.size() / 2;
        vector<ListNode*> sub_l1;
        vector<ListNode*> sub_l2;
        
        for (int i = 0; i < mid; ++i) {
            sub_l1.push_back(lists[i]);
        }
        
        for (int i = mid; i < lists.size(); ++i) {
            sub_l2.push_back(lists[i]);
        }
        
        ListNode* left = mergeKLists(sub_l1);
        ListNode* right = mergeKLists(sub_l2);
        
        return mergeSort(left, right);
    }
    
private:
    ListNode* mergeSort(ListNode* l1, ListNode* l2) {
        ListNode dummy{0};
        ListNode* cur = &dummy;
        
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        cur->next = l1 ? l1 : l2;
        
        return dummy.next;
    }
};

/*
solution 2: divide and conquer + merge sort
time: O(nklogk), k is the number of the lists, n is the length of each list
space: O(logk), stack space
*/

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return helper(lists, 0, lists.size() - 1);
    }
    
    ListNode* helper(const vector<ListNode *> &lists, int start, int end) {
        if (start == end) return lists[start];
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        return mergeSort(helper(lists, start, mid), helper(lists, mid + 1, end));
    }

private:
    ListNode* mergeSort(ListNode* l1, ListNode* l2) {
        ListNode dummy{0};
        ListNode* cur = &dummy;
        
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        cur->next = l1 ? l1 : l2;
        
        return dummy.next;
    }    
    
};

/*
solution 3: mini heap
time: O(nklogk), k is the number of the lists, n is the length of each list. 
Each operation in heap is logk, it has total n*k nodes.
space: O(k), heap space
*/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        struct compare{
            bool operator() (const ListNode* l1, const ListNode* l2){
                return l1->val > l2->val;
            }
        };
        
        // use mini heap to keep track the smallest node of each list
        priority_queue<ListNode*, vector<ListNode*>, compare> mini_heap;
        for (const auto& n : lists) {
            if (n != nullptr) 
                mini_heap.push(n);
        }
        
        ListNode dummy{0};
        ListNode* cur = &dummy;
        
        while (!mini_heap.empty()) {
            auto node = mini_heap.top(); mini_heap.pop();
            cur->next = node;
            cur = cur->next;
            if (node->next != nullptr)
                mini_heap.push(node->next);
        }
        
        return dummy.next;
    }
};