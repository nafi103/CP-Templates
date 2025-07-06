vector<int> prefix_function(string &s) {
    int n = (int)s.length();
    vector<int> pie(n);
    for (int i = 1; i < n; i++) {
        int j = pie[i-1];
        while (j > 0 && s[i] != s[j])
            j = pie[j-1];
        if (s[i] == s[j])
            j++;
        pie[i] = j;
    }
    return pie;
}

int find_occurence(string &a, string &b, vector<int>&pref_func){
    int n = sz(a),m = sz(b), ans = 0, j = 0;
    for(int i = 0; i<n; i++){
        if(j<m and a[i]==b[j])
            j++;
        else if(j!=0){
            j = pref_func[j-1];
            while(j>0 and a[i]!=b[j])
            j = pref_func[j-1];
            if(a[i]==b[j])
            j++;
        }
        if(j==m)
            ans++;
    }
    return ans;
}