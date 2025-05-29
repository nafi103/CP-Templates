struct LCS{
    int n,m;
    string a,b;
    vector<vector<int>>dp;
    LCS(string &_a, string &_b){
        a = _a;
        b = _b;
        n = sz(a); 
        m = sz(b);
        dp.assign(n+1,vector<int>(m+1,0));
        for(int i = n-1; i>=0; i--){
            for(int j = m-1; j>=0; j--){
                if(a[i]==b[j]){
                    dp[i][j] = 1+dp[i+1][j+1];
                }else{
                    dp[i][j] = max(dp[i+1][j],dp[i][j+1]);
                }
            }
        }
    }
    string find_LCS(){
        string lcs = "";
        int i = 0, j = 0, len = dp[0][0];
        while(len){
            bool flag = false;
            for(char c = 'a'; c<='z'; c++){ // maximum LCS 'a' -> 'z'
                for(int p = i; p<n; p++){
                    if(a[p]!=c)
                        continue;
                    for(int q = j; q<m; q++){
                        if(b[q]!=c or dp[p][q]!=len)
                            continue;
                        lcs.push_back(c);
                        i = p+1;
                        j = q+1;
                        c = 'z';
                        len--;
                        p = inf;
                        break;
                    }
                }
            }
        }
        return lcs;
    }
};