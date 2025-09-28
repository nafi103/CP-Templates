void dfs(int v, vector<vector<int>> const& g, vector<int>& output) {
    visited[v] = true;
    for (auto u : g[v])
        if (!visited[u])
            dfs(u, g, output);
    output.push_back(v);
}

void strongly_connected_components(vector<vector<int>> const& g,
                                vector<vector<int>>& components,
                                vector<vector<int>>& g_cond,
                                vector<int>& roots) {
    int n = sz(g);
    components.clear(); g_cond.clear();

    vector<int> order;
    visited.assign(n, false);

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(i, g, order);

    vector<vector<int>> g_rev(n);
    for (int v = 0; v < n; ++v)
        for (int u : g[v])
            g_rev[u].push_back(v);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    roots.assign(n, -1);
    int component_id = 0;

    for (int v : order) {
        if (!visited[v]) {
            vector<int> component;
            dfs(v, g_rev, component);
            for (int u : component)
                roots[u] = component_id;
            components.push_back(component);
            component_id++;
        }
    }

    g_cond.assign(component_id, {});
    for (int v = 0; v < n; ++v) {
        for (int u : g[v]) {
            if (roots[v] != roots[u]) {
                g_cond[roots[v]].push_back(roots[u]);
            }
        }
    }
}