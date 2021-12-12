//Implement a first in first out (FIFO) queue using only two stacks. The impleme
//nted queue should support all the functions of a normal queue (push, peek, pop, 
//and empty). 
//
// Implement the MyQueue class: 
//
// 
// void push(int x) Pushes element x to the back of the queue. 
// int pop() Removes the element from the front of the queue and returns it. 
// int peek() Returns the element at the front of the queue. 
// boolean empty() Returns true if the queue is empty, false otherwise. 
// 
//
// Notes: 
//
// 
// You must use only standard operations of a stack, which means only push to to
//p, peek/pop from top, size, and is empty operations are valid. 
// Depending on your language, the stack may not be supported natively. You may 
//simulate a stack using a list or deque (double-ended queue) as long as you use o
//nly a stack's standard operations. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MyQueue", "push", "push", "peek", "pop", "empty"]
//[[], [1], [2], [], [], []]
//Output
//[null, null, null, 1, 1, false]
//
//Explanation
//MyQueue myQueue = new MyQueue();
//myQueue.push(1); // queue is: [1]
//myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
//myQueue.peek(); // return 1
//myQueue.pop(); // return 1, queue is [2]
//myQueue.empty(); // return false
// 
//
// 
// Constraints: 
//
// 
// 1 <= x <= 9 
// At most 100 calls will be made to push, pop, peek, and empty. 
// All the calls to pop and peek are valid. 
// 
//
// 
// Follow-up: Can you implement the queue such that each operation is amortized 
//O(1) time complexity? In other words, performing n operations will take overall 
//O(n) time even if one of those operations may take longer. 
// Related Topics Stack Design Queue 
// 👍 2325 👎 183


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two stacks, slow version
 * time: O(N)
 * space: O(N)
 * */
class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) { // O(N)
        stack<int> buffer;
        while (!st.empty()) {
            buffer.push(st.top());
            st.pop();
        }

        st.push(x);
        while (!buffer.empty()) {
            st.push(buffer.top());
            buffer.pop();
        }
    }

    int pop() { // O(1)
        int val = st.top();
        st.pop();
        return val;
    }

    int peek() { // O(1)
        return st.top();
    }

    bool empty() { // O(1)
        return st.size() == 0;
    }

    stack<int> st;
};


/*
 * solution 1: two stacks, fast version
 * time: O(N)
 * space: O(N)
 * */

//为什么这个方法更快？因为解法一中O(n)全部压在了push，而此解法中将O(n)集中在了pop和peek，平均时间复杂度为O(1)
class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) { //O(1)
        rawStack.push(x);
    }

    int pop() { // amortized O(1)
        shiftStack();
        int val = buffer.top();
        buffer.pop();
        return val;
    }

    int peek() { // amortized O(1)
        shiftStack();
        return buffer.top();
    }

    bool empty() { // O(1)
        return rawStack.empty() && buffer.empty();
    }

    void shiftStack() { // O(n)
        // 为什么要多这一步？因为在调用peek后实现了shift，但是没有还原原始stack
        if (!buffer.empty()) {
            return;
        }

        while (!rawStack.empty()) {
            buffer.push(rawStack.top());
            rawStack.pop();
        }
    }

    stack<int> rawStack, buffer;
};
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
//leetcode submit region end(Prohibit modification and deletion)
