class Solution {
public:
    string getHint(string secret, string guess) {
    	int a = 0, b = 0;
    	vector<int> count(10);
    	for(int i = 0; i < secret.size(); ++i){
    		if(secret[i] == guess[i]){
    			a++;
    		} else{
    			if(count[secret[i] - '0']++ < 0 ) b++;
    			if(count[guess[i]-- - '0']-- > 0) b++;
    		}
    	}

    	return to_string(a) + "A" + to_string(b) + "B";
    }
};

