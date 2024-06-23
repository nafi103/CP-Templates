class ele
{
    public:
    int u, v, wt;
};
class check
{
    public:
    bool operator()(ele a, ele b)
    {
        return a.wt > b.wt;
    }
};
struct Graph{
    vector<vpi>v;
    int n;
    Graph(int N){
        v.resize(N+1);
        n = N;
    }
    void add(int uu, int vv, int wt){
        v[uu].pb({vv,wt});
        v[vv].pb({uu,wt});
    }
    pair<vpi,int> makeMST(int start){
        vpi mst;
        int cost = 0;
        priority_queue<ele, vector<ele>, check> pq;
        vector<bool>visited(n+1,false);
        for (auto x : v[start])
        {
            pq.push({start,x.first,x.second});
        };
        visited[start] = true;
        while(!pq.empty()){
            auto z = pq.top();
            pq.pop();
            if(visited[z.v]) continue;
            else{
                visited[z.v] = true;
                mst.push_back({z.u,z.v});
                cost+=z.wt;
                for(auto x: v[z.v]){
                    pq.push({z.v,x.first,x.second});
                }
            }
        }
        return {mst,cost};
    }
    vector<int> dijsktra(int src)
    {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vi distance(n, INT_MAX);
        distance[src] = 0;
        pq.push({0, src});
        while (!pq.empty())
        {
            pii p = pq.top();
            pq.pop();
            for (auto &[nbr,wt] : v[p.second])
            {
                if (distance[nbr] > distance[p.second] + wt)
                {
                    distance[nbr] = distance[p.second] + wt;
                    pq.push({distance[nbr], nbr});
                }
            }
        }
        return distance;
    }
};