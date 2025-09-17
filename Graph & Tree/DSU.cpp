struct DSU{
    vector<int>parent, _size;

    DSU(int n){
        parent.resize(n);
        iota(all(parent),0);
        _size.assign(n,1); 
    }
 
    int find(int i){ 
        if(parent[i]==i) return i; 
        return parent[i] = find(parent[i]); 
    } 
    
    int size(int a){ 
        a = find(a); 
        return _size[a]; 
    }

    bool same_group(int a, int b){
        return find(a)==find(b);
    }
    
    void Union(int a, int b){ 
        a = find(a); 
        b = find(b); 
        if(a==b) return; 
        if(_size[a]<_size[b]) swap(a,b);
        parent[b] = a; 
        _size[a]+=_size[b]; 
    }
};