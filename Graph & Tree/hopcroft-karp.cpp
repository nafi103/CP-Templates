// ...existing code...

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> g;
    vector<int> dist, pairU, pairV;
    static const int INF = 1e9;

    HopcroftKarp(int n_ = 0, int m_ = 0) {
        n = n_; m = m_;
        g.assign(n, {});
        pairU.assign(n, -1);
        pairV.assign(m, -1);
        dist.assign(n, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        bool foundAug = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                int u2 = pairV[v];
                if (u2 == -1) {
                    foundAug = true;
                } else if (dist[u2] == INF) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return foundAug;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < n; ++u)
                if (pairU[u] == -1 && dfs(u))
                    ++matching;
        }
        return matching;
    }

    vector<pair<int,int>> matching_edges() const {
        vector<pair<int,int>> res;
        for (int v = 0; v < m; ++v)
            if (pairV[v] != -1) res.emplace_back(pairV[v], v);
        return res;
    }
};