struct Hashing{
    string s;
    int n;
    int primes;
    vector<int> hashPrimes = {1000000009};
    const int base = 31;
    vector<vector<int>> hashValues;
    vector<vector<int>> powersOfBase;
    vector<vector<int>> inversePowersOfBase;
    Hashing(string a){
        primes = sz(hashPrimes);
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length(); 
        for(int i = 0; i < sz(hashPrimes); i++) {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for(int j = 1; j <= n; j++){
                powersOfBase[i][j] = (base * powersOfBase[i][j - 1]) % hashPrimes[i];
            }
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);
            for(int j = n - 1; j >= 0; j--){
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            } 
        }
        for(int i = 0; i < sz(hashPrimes); i++) {
            hashValues[i].resize(n);
            for(int j = 0; j < n; j++){
                hashValues[i][j] = ((s[j] - 'a' + 1ll) * powersOfBase[i][j]) % hashPrimes[i];
                hashValues[i][j] = (hashValues[i][j] + (j > 0 ? hashValues[i][j - 1] : 0ll)) % hashPrimes[i];
            }
        }
    }
    vector<int> substringHash(int l, int r){
        vector<int> hash(primes);
        for(int i = 0; i < primes; i++){
            int val1 = hashValues[i][r];
            int val2 = l > 0 ? hashValues[i][l - 1] : 0ll;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
};

bool palindromeFound(int k, Hashing& original, Hashing& reversed, int n){
    for(int i = 0; i <= n - k; i++){
        int l1 = i, r1 = i + k - 1;
        int l2 = n - r1 - 1, r2 = n - l1 - 1;
        if(original.substringHash(l1, r1) == reversed.substringHash(l2, r2)){
            return true;
        }
    }
    return false;
}

int longestPalindrome(vi& lengths, Hashing& original, Hashing& reversed, int n){
    int ans = 0;
    int start = 0, end = lengths.size() - 1;
    while(start <= end){
        int mid = (start + end) / 2;
        if(palindromeFound(lengths[mid], original, reversed, n)){
            ans = max(ans, lengths[mid]);
            start = mid + 1;
        }else{
            end = mid - 1;
        }
    }
    return ans;
}

int findLongestPalindrome(int n, Hashing &originalH, Hashing &reversedH){
    vi oddLength, evenLength;
    for(int i = 1; i <= n; i++){
        if(i & 1){
            oddLength.push_back(i);
        }else{
            evenLength.push_back(i);
        }
    } 
    int ans1 = longestPalindrome(oddLength, originalH, reversedH, n);
    int ans2 = longestPalindrome(evenLength, originalH, reversedH, n);
    return max(ans1, ans2);
}
