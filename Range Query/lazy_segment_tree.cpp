const int mt = 0;

struct Lazy_Segment_Tree{
    int n;
    vector<int>v,lazy,st;

    Lazy_Segment_Tree(vector<int>&_v,int _n){
        n = _n;
        st.resize(4*n);
        lazy.resize(4*n,0);
        v = _v;
        build(1,1,n);
    }
    
    void build(int node, int b, int e){
        if(b==e){
            st[node] = v[b];
            return;
        }
        int mid = (b+e)/2,left = 2*node, right = 2*node+1;
        build(left, b, mid);
        build(right, mid+1,e);
        st[node] = st[left]+st[right];
    }
    
    void propagate(int node, int b, int e){
        if(lazy[node]==mt)
            return;
        st[node]+=((e-b+1)*lazy[node]);
        if(b!=e){
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    
    void update(int node, int b, int e, int &l, int &r, int &value){
        propagate(node, b, e);
        if(e<l or b>r) return;
        if(b>=l and e<=r){
            lazy[node] = value;
            propagate(node,b,e);
            return;
        }
        int mid = (b+e)/2,left = 2*node, right = 2*node+1;
        update(left, b, mid,l,r,value);
        update(right, mid+1,e,l,r,value);
        st[node] = st[left]+st[right];
    }
    
    int query(int node, int b, int e, int &l, int &r){
        propagate(node, b, e);
        if(e<l or b>r) return 0;
        if(b>=l and e<=r){
            return st[node];
        }
        int mid = (b+e)/2, left = 2*node, right = 2*node+1;
        return query(left,b,mid,l,r) + query(right,mid+1,e,l,r);
    }
};