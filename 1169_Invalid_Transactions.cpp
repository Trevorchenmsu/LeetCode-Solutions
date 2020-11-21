/*
solution 1: brute force
time: O(n^2)
space: O(n)
*/
class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        vector<vector<string> > trans;
        
        for(auto t :transactions){
            vector<string> tran = split(t, ',');
            trans.push_back(tran);
        }
        
        set<string> invalidTrans;
        
        for(int i = 0; i < trans.size(); ++i){
            bool flag = false;
            for(int j = i + 1; j < trans.size(); ++j){
                if(trans[i][3] == trans[j][3] || trans[i][0] != trans[j][0]){
                    continue;
                }
                if(abs(atoi(trans[i][1].c_str()) - atoi(trans[j][1].c_str())) <= 60){
                    invalidTrans.insert(transactions[j]);
                    flag = true;
                }
            }
            if(flag){
                invalidTrans.insert(transactions[i]);
            }
            
            if(atoi(trans[i][2].c_str()) > 1000){
                invalidTrans.insert(transactions[i]);
            }
        }
        
        vector<string> res(invalidTrans.begin(), invalidTrans.end());

        return res;
    }
    
    vector<string> split(const string& s, char delim) {
		vector<string> res;
		stringstream ss(s);
		string token;
		while (getline(ss, token, delim)) {
			if (token != "\0") {
				res.push_back(token);
			}
		}
		return res;
	}
};

/*
solution 2: brute force
time: O(n^2)
space: O(n)
*/
struct Tran{
    string name;
    int time;
    int amount;
    string city;
};

class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        vector<Tran> trans;
        set<string> invalidTrans;
        
        for(auto t : transactions){
            vector<string> ts = split(t, ',');
            trans.push_back({ts[0], stoi(ts[1]), stoi(ts[2]), ts[3]});
        }

        for(int i = 0; i < trans.size(); ++i){
            bool flag = false;
            for(int j = i + 1; j < trans.size(); ++j){
                if(trans[i].city == trans[j].city || trans[i].name != trans[j].name){
                    continue;
                }
                if(abs(trans[i].time - trans[j].time) <= 60){
                    invalidTrans.insert(transactions[j]);
                    flag = true;
                }
            }
            if(flag){
                invalidTrans.insert(transactions[i]);
            }
            
            if(trans[i].amount > 1000){
                invalidTrans.insert(transactions[i]);
            }
        }
        
        vector<string> res(invalidTrans.begin(), invalidTrans.end());

        return res;
    }
    
    vector<string> split(const string& s, char delim) {
		vector<string> res;
		stringstream ss(s);
		string token;
		while (getline(ss, token, delim)) {
			if (token != "\0") {
				res.push_back(token);
			}
		}
		return res;
	}
};