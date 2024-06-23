vector<int> v, t;

void buildSegTree(int node, int b, int e){
    if(b==e){
        t[node] = v[e];
        return;
    }
    int left = 2*node, right = 2*node+1, mid = (b+e)/2;
    buildSegTree(left, b, mid);
    buildSegTree(right, mid+1, e);
    t[node] = t[left]+t[right];
}

void update(int node, int b,int e, int i, int x){
    if(b==e and e==i){
        t[node] = x;
        return;
    }
    int left = 2*node, right = 2*node+1, mid = (b+e)/2;
    if(i<=mid) update(left, b,mid, i, x);
    else update(right, mid+1, e, i, x);
    t[node] = t[left]+t[right];
}

int query(int node, int b, int e, int l, int r){
    if(r<b or l>e){
        return 0;
    }
    if(b>=l and e<=r)   return t[node];
    int left = 2*node, right = 2*node+1, mid = (b+e)/2;
    return query(left,b,mid,l,r)+query(right,mid+1,e,l,r);
}