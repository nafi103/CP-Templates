vector<vector<int>>parents;
vector<vector<pair<int,int>>>t;
vector<int>level,value,subtree_size, heavy_child, head, id,st;
int mx;

void build(int &n) {
    for (int i = n - 1; i > 0; --i) st[i] = max(st[i<<1] , st[i<<1|1]);
}

int query(int l, int r, int &n) {
    int res = INT_MIN;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = max(res, st[l++]);
        if (r&1) res = max(res, st[--r]);
    }
    return res;
}

int dfs(int node, int parent, int cLevel){
    int max_subtree_size = 0;
    level[node] = cLevel;
    parents[0][node] = parent;
    for(auto &[child,weight]: t[node]){
        if(child!=parent){
            dfs(child,node, cLevel+1);
            subtree_size[node]+=subtree_size[child];
            if(subtree_size[child]>max_subtree_size){
                max_subtree_size = subtree_size[child];
                heavy_child[node] = child;
            }
        }
    }
    return subtree_size[node];
}

void dfs_complete(int node, int parent, int weight, int &curr_id,int &n){
    id[node] = curr_id++;
    st[curr_id+n-1] = weight;
    if(head[node]==-1){
        head[node] = node;
    }
    if(heavy_child[node]!=-1){
        int weight = 0;
        for(auto &[child,wt]: t[node]){
            if(child==heavy_child[node]){
                weight = wt;
                break;
            }
        }
        head[heavy_child[node]] = head[node];
        dfs_complete(heavy_child[node],node,weight, curr_id,n);
    }
    for(auto &[child,weight]: t[node]){
        if(child!=parent and child!=heavy_child[node]) dfs_complete(child, node,weight, curr_id,n);
    }
}

int kthParent(int a, int k){
    for(int i = 0; i<mx; i++){
        if(a==-1) return a;
        if(k&(1<<i)) a = parents[i][a];
    }
    return a;
}

int lca(int a, int b){
    if(level[a]>level[b]){
        a = kthParent(a, level[a] - level[b]);
    }else{
        b = kthParent(b, level[b] - level[a]);
    }
    if(a==b) return a;
    for(int i = mx-1; i>=0; i--){
        if(parents[i][a]!=parents[i][b]){
            a = parents[i][a];
            b = parents[i][b];
        }
    }
    return parents[0][a];
}

int path_ans(int a, int b, int &n){
    int LCA = lca(a,b),ans = 0;
    while(head[a] != head[LCA]){
        ans = max(ans, query(id[head[a]], id[a]+1, n));
        a = parents[0][head[a]];
    }
    if(a != LCA) {
        ans = max(ans, query(id[LCA]+1, id[a]+1, n));
    }
    while(head[b] != head[LCA]){
        ans = max(ans, query(id[head[b]], id[b]+1, n));
        b = parents[0][head[b]];
    }
    if(b != LCA) {
        ans = max(ans, query(id[LCA]+1, id[b]+1, n));
    }
    return ans;
}

void initialize(int n){
    t.resize(n+1);
    parents.assign(mx,vector<int>(n+1,-1));
    subtree_size.resize(n+1,1);
    id.resize(n+1);
    heavy_child.assign(n+1,-1);
    head.assign(n+1,-1);
    st.resize(2*n);
    level.resize(n+1);
    value.resize(n+1);
}

void clear_all(){
    t.clear();
    parents.clear();
    subtree_size.clear();
    id.clear();
    heavy_child.clear();
    head.clear();
    st.clear();
    level.clear();
    value.clear();
}

void solve()
{
    int n,m;
    cin>>n>>m;
    mx = log2(n) + 2;
    initialize(n);
    while(m--){
        int u,v,w;
        cin>>u>>v>>w;
        t[u].push_back({v,w});
        t[v].push_back({u,w});
    }
    dfs(1,-1,0);
    int curr_id = 0;
    dfs_complete(1,-1,0,curr_id,n);
    build(n);
    for(int i = 1; i<mx; i++){
        for(int j = 1; j<=n; j++){
            int prevParent = parents[i-1][j];
            if(prevParent!=-1)  parents[i][j] = parents[i-1][prevParent];
        }
    }
    int q;
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        cout<<path_ans(a,b,n)<<endl;
    }
    clear_all();
}