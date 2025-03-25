//Precalculate parents first in main

vector<vi>t,parents;
vector<int>level; 
int mx;

void dfs(int node, int parent, int cLevel){
    level[node] = cLevel;
    parents[0][node] = parent;
    for(auto &x: t[node]){
        if(x!=parent) dfs(x,node, cLevel+1);
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

int distance(int a,int b){
    return level[a]+level[b] - 2*level[lca(a,b)];
}
