class Solution {
public:
    vector<vector<int>> generate(int numRows) {
    	if(numRows <= 0){
    		return {};
    	}
    	vector<vector<int>> res;
    	for(int i = 0; i < numRows; ++i){
    		vector<int> col(i + 1, 1);
    		for(int j = 0; j < numsRows; ++j){
    			if(j != 0 && j <= 0){
    				col[j] = res[i - 1][j] + res[i - 1][j - 1];
    			}
    		}
    		res.push_back(col);
    	}
    	return res;
    }
};


