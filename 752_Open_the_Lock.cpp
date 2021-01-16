/*
solution 1: BFS
time: O(n^m + d), n is the number of digits, m is the number of lock rollers, d is the size of deadends
space:O(n^m + d)
*/

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if (deadends.empty() || deadends.size() == 0)
            return -1;
        
        queue<string> q{{"0000"}};
        unordered_set<string> dead(deadends.begin(), deadends.end()); // O(n), n i sht size of deadends
        unordered_set<string> visited;
        visited.insert("0000");
        
        int res = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string cur = q.front(); q.pop();
                if (dead.count(cur)) continue;
                if (cur == target) return res;
                for (int j = 0; j < cur.size(); ++j) {
                    string up = plusOne(j, cur);
                    string down = minusOne(j, cur);
                    if (!dead.count(up) && !visited.count(up)) {
                        q.push(up);
                        visited.insert(up);
                    }  
                    if (!dead.count(down) && !visited.count(down)) {
                        q.push(down);
                        visited.insert(down);
                    }  
                }
            }
            res++;
        }
        
        return -1;
    }

private:
    string plusOne(int j, string s) {
        string res = s;
        if (res[j] == '9') res[j] = '0';
        else res[j] += 1;
        return res;
    }
    
    string minusOne(int j, string s) {
        string res = s;
        if (res[j] == '0') res[j] = '9';
        else res[j] -= 1;
        return res;
    }
};

/*
solution 2: double BFS
time: O(n^m + d), n is the number of digits, m is the number of lock rollers, d is the size of deadends
space:O(n^m + d)
*/
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if (deadends.empty() || deadends.size() == 0)
            return -1;
        
        unordered_set<string> dead(deadends.begin(), deadends.end()); // O(d)
        unordered_set<string> visited;
        visited.insert("0000");

        unordered_set<string> forward;
        unordered_set<string> backward;
        forward.insert("0000");
        backward.insert(target);
        
        int res = 0;

        while (!forward.empty() && !backward.empty()) {
        	unordered_set<string> temp;

        	for (string cur : forward) {
        		if (dead.count(cur)) continue;
        		if (backward.count(cur)) return res;
        		visited.insert(cur);
        		for (int j = 0; j < cur.size(); ++j) {
	                string up = plusOne(j, cur);
	                string down = minusOne(j, cur);
	                if (!visited.count(up)) temp.insert(up);	                                    
	                if (!visited.count(down)) temp.insert(down);	                      
                }
        	}
            res++;
            forward = backward;
            backward = temp;
        }      
        return -1;
    }

private:
    string plusOne(int j, string s) {
        string res = s;
        if (res[j] == '9') res[j] = '0';
        else res[j] += 1;
        return res;
    }
    
    string minusOne(int j, string s) {
        string res = s;
        if (res[j] == '0') res[j] = '9';
        else res[j] -= 1;
        return res;
    }
};
