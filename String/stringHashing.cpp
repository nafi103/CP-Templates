vi hashPrimes = {1000000009, 100000007};
vector<vi> powersOfBase,inversePowersOfBase;

void findInversePower(int primes, int n){
    const int base = 31;
    powersOfBase.resize(primes);
    inversePowersOfBase.resize(primes);
    for(int i = 0; i < hashPrimes.size(); i++) {
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
}

struct Hashing{
    string s;
    int n;
    int primes;
    vector<vi> hashValues;
    Hashing(string a){
        primes = hashPrimes.size();
        hashValues.resize(primes);
        s = a;
        n = s.length();
        if(inversePowersOfBase.empty()) findInversePower(primes,n);
        for(int i = 0; i < hashPrimes.size(); i++) {
            hashValues[i].resize(n);
            for(int j = 0; j < n; j++){
                hashValues[i][j] = ((s[j] - 'a' + 1ll) * powersOfBase[i][j]) % hashPrimes[i];
                hashValues[i][j] = (hashValues[i][j] + (j > 0ll ? hashValues[i][j - 1] : 0ll)) % hashPrimes[i];
            }
        }
    }
    vi substringHash(int l, int r){
        vi hash(primes);
        for(int i = 0; i < primes; i++){
            int val1 = hashValues[i][r];
            int val2 = l > 0ll ? hashValues[i][l - 1] : 0ll;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
    bool compareSubstrings(int l1, int r1, int l2, int r2){
        if(l1 > l2){
            swap(l1, l2);
            swap(r1, r2);
        }
        for(int i = 0; i < primes; i++){
            int val1 = mod_sub(hashValues[i][r1], (l1 > 0 ? hashValues[i][l1 - 1] : 0LL), hashPrimes[i]);
            int val2 = mod_sub(hashValues[i][r2], (l2 > 0 ? hashValues[i][l2 - 1] : 0LL), hashPrimes[i]);
            if(mod_mul(val1, powersOfBase[i][l2 - l1], hashPrimes[i]) != val2)
                return false;
        }   
        return true;
    }
};

bool palindromeFound(int k, Hashing& original, Hashing& reversed, int n){
    for(int i = 0; i <= n - k; i++){
        int l1 = i, r1 = i + k - 1;
        int l2 = n - r1 - 1, r2 = n - r2 - 1;
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