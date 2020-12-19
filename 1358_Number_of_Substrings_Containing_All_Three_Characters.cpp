class Solution {
    int cnt[3];
public:
    int numberOfSubstrings(string s) {
        int len=(int)s.length(),ans=0;
        cnt[0]=cnt[1]=cnt[2]=0;
        for (int l=0,r=-1;l<len;){
            while (r<len && !(cnt[0]>=1 && cnt[1]>=1 && cnt[2]>=1)){
                if (++r==len) break;
                cnt[s[r]-'a']++;
            }
            ans+=len-r;
            cnt[s[l++]-'a']--;
        }
        return ans;
    }
};