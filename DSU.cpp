//Template for DSU

vector<int>parent, _size; 
 
int find(int i){ 
    if(parent[i]==i) return i; 
    return parent[i] = find(parent[i]); 
} 
 
int size(int a){ 
    a = find(a); 
    return _size[a]; 
} 
 
void Union(int a, int b){ 
    a = find(a); 
    b = find(b); 
    if(a==b) return; 
    if(_size[a]<_size[b]) swap(a,b); //union by size 
    parent[b] = a; 
    _size[a]+=_size[b]; 
} 
 
void solve(){
    int n,k; 
    cin>>n>>k; 
    parent.resize(n+1); 
    _size.assign(n+1,1); 
    for(int i = 1; i<=n; i++) 
        parent[i] = i; 
    while(k--){ 
        int u,v; 
        cin>>u>>v; 
        Union(u,v); 
    } 
}
