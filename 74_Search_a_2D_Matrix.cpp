// solution 1: binary search

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
    	// corner case
    	if (matrix.empty() || matrix.size() == 0){
    		return false;
    	}

    	if(matrix[0].empty() || matrix[0].size() == 0){
    		return false;
    	}

    	int m = matrix.size();
    	int n = matrix[0].size();

    	// binary search
    	int start = 0, end = m * n - 1;
    	while(start + 1 < end){
    		int mid = start + (end - start) / 2;
    		int val = matrix[mid / n][mid % n];
    		if(val == target){
    			return true;
    		} else if (val > target){
    			end = mid;
    		} else{
    			start = mid;
    		}
    	}

    	if(target == matrix[start / n][start % n]){
    		return true;
    	}

    	if(target == matrix[end / n][end % n]){
    		return true;
    	}

    	return false;
    }
};


 