class Solution{
public:
	int findCelebrity(int n) {
		 if (n < 2) 
		 	return -1;
		int cele = 0;
		for(int i = 1; i < n; ++i){
			if(knows(cele, i))
				cele = i;
		}
		for (int i = 0; i < n; ++i) {
            if (cele != i && ((knows(cele, i) || !knows(i, cele)))) {
                return -1;
            }
        }
		return cele;
	}
};


    