/*
Solution: 
time: O(S), S is the length of the source code
space: O(S), the worst case is we need to store all the characters of the source code. 
*/

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> res;
        bool blocked = false;
        string out = "";
        for (string line : source) {
            for (int i = 0; i < line.size(); ++i) {
                if (!blocked) {
                    if (i == line.size() - 1) out += line[i];
                    else {
                        string t = line.substr(i, 2);
                        if (t == "/*") blocked = true, ++i;
                        else if (t == "//") break;
                        else out += line[i];
                    }
                } else {
                    if (i < line.size() - 1) {
                        string t = line.substr(i, 2);
                        if (t == "*/") blocked = false, ++i;
                    }
                }
            }
            if (!out.empty() && !blocked) {
                res.push_back(out);
                out = "";
            }
        }
        return res;
    }
};