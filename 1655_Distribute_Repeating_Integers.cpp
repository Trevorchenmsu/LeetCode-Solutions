class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        map<int,int> mark;
        vector<int> val;
        int vis[1050];
        int val_sum[1050];

        memset(vis,0,sizeof(vis));
        for(int i=0;i<nums.size();i++)mark[nums[i]]++;
        for(map<int,int>::iterator it = mark.begin();it!=mark.end();it++){
            val.push_back(it->second);
        }
        for(int l=1;l<(1<<quantity.size());l++){
            int sum=0;
            for(int k=0;k<quantity.size();k++){
                if(l&(1<<k)){
                    sum+=quantity[k];
                }
            }
            val_sum[l]=sum;
        }
        vis[0]=1;
        for(int i=0;i<val.size();i++){
            for(int j=(1<<quantity.size())-1;j>=0;j--){
                if(!vis[j])continue;
                for(int l=1;l<(1<<quantity.size());l++){
                    if(val[i]>=val_sum[l]){
                        vis[j|l]=1;
                    }
                }
            }
            if(vis[(1<<quantity.size())-1])return true;
        }
        return false;
    }
};
