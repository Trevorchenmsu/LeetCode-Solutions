//Design a max stack data structure that supports the stack operations and suppo
//rts finding the stack's maximum element. 
//
// Implement the MaxStack class: 
//
// 
// MaxStack() Initializes the stack object. 
// void push(int x) Pushes element x onto the stack. 
// int pop() Removes the element on top of the stack and returns it. 
// int top() Gets the element on the top of the stack without removing it. 
// int peekMax() Retrieves the maximum element in the stack without removing it.
// 
// int popMax() Retrieves the maximum element in the stack and removes it. If th
//ere is more than one maximum element, only remove the top-most one. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MaxStack", "push", "push", "push", "top", "popMax", "top", "peekMax", "pop",
// "top"]
//[[], [5], [1], [5], [], [], [], [], [], []]
//Output
//[null, null, null, null, 5, 5, 1, 5, 1, 5]
//
//Explanation
//MaxStack stk = new MaxStack();
//stk.push(5);   // [5] the top of the stack and the maximum number is 5.
//stk.push(1);   // [5, 1] the top of the stack is 1, but the maximum is 5.
//stk.push(5);   // [5, 1, 5] the top of the stack is 5, which is also the maxim
//um, because it is the top most one.
//stk.top();     // return 5, [5, 1, 5] the stack did not change.
//stk.popMax();  // return 5, [5, 1] the stack is changed now, and the top is di
//fferent from the max.
//stk.top();     // return 1, [5, 1] the stack did not change.
//stk.peekMax(); // return 5, [5, 1] the stack did not change.
//stk.pop();     // return 1, [5] the top of the stack and the max element is no
//w 5.
//stk.top();     // return 5, [5] the stack did not change.
// 
//
// 
// Constraints: 
//
// 
// -107 <= x <= 107 
// At most 104 calls will be made to push, pop, top, peekMax, and popMax. 
// There will be at least one element in the stack when pop, top, peekMax, or po
//pMax is called. 
// 
//
// 
//Follow up: Could you come up with a solution that supports O(1) for each top c
//all and O(logn) for each other call? Related Topics Design 
// 👍 927 👎 225


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: two stacks
 * time: O(n)
 * space: O(n)
 * */
class MaxStack {
public:
    MaxStack() {

    }

    void push(int x) {
        st.push(x);
        if (maxSt.empty() || x > maxSt.top()) {
            maxSt.push(x);
        }
        else {
            maxSt.push(maxSt.top());
        }
    }

    int pop() {
        int val = st.top();
        st.pop();
        maxSt.pop();
        return val;
    }

    int top() {
        return st.top();
    }

    int peekMax() {
        return maxSt.top();
    }

    int popMax() {
        int val = maxSt.top();
        while (st.top() != val) {
            buffer.push(pop());
        }
        pop();
        while (!buffer.empty()) {
            push(buffer.top());
            buffer.pop();
        }
        return val;
    }

    stack<int> st, maxSt, buffer;
};


/*
 * Solution 2: list + treemap, follow up
 * time: O(logN)
 * space: O(N)
 * */

class MaxStack {
public:
    MaxStack() {

    }

    // 链表直接插入值，同时更新映射。以链表尾作为对应的迭代器位置，因为在链表中是插到尾巴的
    void push(int x) { // O(logN)
        valueList.push_back(x);
        valToiter[x].push_back(--valueList.end());
    }

    int pop() { // O(logN)
        // 首先获取链表尾元素用作返回值，然后删除该元素
        int val = valueList.back();
        valueList.pop_back();

        // 从值对应的迭代器数组中删除最后一个迭代器，可能有多个重复元素，所以删除后要判定size，如果为0，key就要删除
        valToiter[val].pop_back();
        if (valToiter[val].size() == 0) {
            valToiter.erase(val);
        }

        return val;
    }

    int top() { // O(1)
        return valueList.back();
    }

    int peekMax() { // O(1)
        // 原来哈希表中也可以用end()作为迭代器来获取元素
        return (--valToiter.end())->first;
    }

    int popMax() { // O(logN)
        // 从treemap中获取最大元素，因为自动排序，只需要获取最后一个
        int val = (--valToiter.end())->first;
        // 这里用val获取迭代器的原因是，在链表中最大值不一定是链表尾，所以需要用迭代器的位置进行删除
        auto iter = valToiter[val].back();
        valueList.erase(iter);

        // 因为删除了一个最大值，所以需要从对应的迭代器数组中删除一个迭代器，如果size0，就删除key
        valToiter[val].pop_back();
        if (valToiter[val].size() == 0) {
            valToiter.erase(val);
        }

        return val;
    }

    // 采用链表存储插入值，采用treemap实现值映射迭代器，因为可能有重复元素，所以用数组存迭代器
    list<int> valueList;
    map<int, vector<list<int>::iterator>> valToiter;
};


/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
//leetcode submit region end(Prohibit modification and deletion)
