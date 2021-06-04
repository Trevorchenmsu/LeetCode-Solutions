//You are given n tasks labeled from 0 to n - 1 represented by a 2D integer arra
//y tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the ith tas
//k will be available to process at enqueueTimei and will take processingTimei to 
//finish processing. 
//
// You have a single-threaded CPU that can process at most one task at a time an
//d will act in the following way: 
//
// 
// If the CPU is idle and there are no available tasks to process, the CPU remai
//ns idle. 
// If the CPU is idle and there are available tasks, the CPU will choose the one
// with the shortest processing time. If multiple tasks have the same shortest pro
//cessing time, it will choose the task with the smallest index. 
// Once a task is started, the CPU will process the entire task without stopping
//. 
// The CPU can finish a task then start a new one instantly. 
// 
//
// Return the order in which the CPU will process the tasks. 
//
// 
// Example 1: 
//
// 
//Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
//Output: [0,2,3,1]
//Explanation: The events go as follows: 
//- At time = 1, task 0 is available to process. Available tasks = {0}.
//- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {
//}.
//- At time = 2, task 1 is available to process. Available tasks = {1}.
//- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
//- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it
// is the shortest. Available tasks = {1}.
//- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
//- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is t
//he shortest. Available tasks = {1}.
//- At time = 6, the CPU finishes task 3 and starts processing task 1. Available
// tasks = {}.
//- At time = 10, the CPU finishes task 1 and becomes idle.
// 
//
// Example 2: 
//
// 
//Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
//Output: [4,3,2,0,1]
//Explanation: The events go as follows:
//- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
//- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {
//0,1,2,3}.
//- At time = 9, the CPU finishes task 4 and starts processing task 3. Available
// tasks = {0,1,2}.
//- At time = 13, the CPU finishes task 3 and starts processing task 2. Availabl
//e tasks = {0,1}.
//- At time = 18, the CPU finishes task 2 and starts processing task 0. Availabl
//e tasks = {1}.
//- At time = 28, the CPU finishes task 0 and starts processing task 1. Availabl
//e tasks = {}.
//- At time = 40, the CPU finishes task 1 and becomes idle.
// 
//
// 
// Constraints: 
//
// 
// tasks.length == n 
// 1 <= n <= 105 
// 1 <= enqueueTimei, processingTimei <= 109 
// 
// Related Topics Heap 
// 👍 120 👎 47


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: pq + vector + sort
 * time: O(n^2*logn)
 * space: O(n)
 *
// * */
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<int> res;
        vector<vector<int>> tasks_sort;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> available;
        int n = tasks.size();
        long time = 0;

        for (int i = 0; i < n; i++) { // O(n)
            tasks_sort.push_back({tasks[i][0], tasks[i][1], i});
        }
        sort(tasks_sort.begin(), tasks_sort.end(), [](const vector<int> &v1, const vector<int> &v2){ //O(nlogn)
            if (v2[0] < v1[0])
                return true;
            else if (v2[0] == v1[0]) {
                if (v2[1] < v1[1])
                    return true;
                else if (v2[1] == v1[1])
                    return v2[2] < v1[2];
            }
            return false;
        });

        while (res.size() < n) {
            // traver the tasks list to see which one is able to be enqueued
            // O(nlogn), L is maximum size of the tasks in the pq at the same time, which can be n
            while (!tasks_sort.empty() && tasks_sort[tasks_sort.size() - 1][0] <= time) {
                addNewTask(available, tasks_sort);
            }

            // the cpu is idle
            if (available.empty()) { // O(1), because pq is empty
                int enq_time = addNewTask(available, tasks_sort);
                time = enq_time + time;
            }

            // process current task, O(logL)
            vector<int> cur_task = available.top();
            available.pop();
            time += cur_task[0];
            res.push_back(cur_task[1]);
        }

        return res;
    }

private:
    int addNewTask( priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> &available,
                     vector<vector<int>> &tasks_sort) {
        vector<int> new_task = tasks_sort[tasks_sort.size() - 1];
        tasks_sort.pop_back();
        int enq_time = new_task[0], pro_time = new_task[1], idx = new_task[2];
        available.push({pro_time, idx});
        return enq_time;
    }
};


/*
 * solution 2: pq
 * time: O(n^2*logn)
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        mini_heap tasks_sort;
        mini_heap available;
        vector<int> res;
        long time = 0;
        int n = tasks.size();

        // first sort by enqueue time, then by index, O(nlogn)
        for (int i = 0; i < tasks.size(); i++) {
            tasks_sort.push({tasks[i][0], i, tasks[i][1]});
        }

        while (res.size() < n) { // O(n)
            // if cpu is idle, assign a task to it
            if (available.empty()) { // O(logn)
                int enq_time = addNewTask(available, tasks_sort);
                time = max((long) enq_time, time);
            }

            // new task available
            while (!tasks_sort.empty() && tasks_sort.top()[0] <= time) { //O(nlogn)
                addNewTask(available, tasks_sort);
            }

            // process the task
            vector<int> cur_task = available.top();
            available.pop();
            time += cur_task[0];
            res.push_back(cur_task[1]);
        }

        return res;
    }

private:
    typedef priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> mini_heap;

    int addNewTask(mini_heap &available, mini_heap &tasks_sort) {
        vector<int> new_task = tasks_sort.top();
        tasks_sort.pop();
        int enq_time = new_task[0], idx = new_task[1], pro_time = new_task[2];
        available.push({pro_time, idx});
        return enq_time;
    }
};



/*
 * solution 3: pq
 * time: O(n^2*logn)
 * space: O(n)
 *
 * */

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<int> res;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> available;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> enqueue;

        for (int i = 0; i < tasks.size(); i++) { // O(nlogn)
            enqueue.push({tasks[i][0], tasks[i][1], i});
        }

        long time = 0;
        while (res.size() < n) {
            if (available.empty()) {
                vector<int> task = enqueue.top();
                enqueue.pop();
                int enqTime = task[0], proTime = task[1], idx = task[2];
                available.push({proTime, idx});
                time = max(time, (long) enqTime);
            }

            while (!enqueue.empty() && enqueue.top()[0] <= time) {
                vector<int> task = enqueue.top();
                enqueue.pop();
                int enqTime = task[0], proTime = task[1], idx = task[2];
                available.push({proTime, idx});
            }

            vector<int> tmp = available.top();
            available.pop();
            res.push_back(tmp[1]);
            time += tmp[0];
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
