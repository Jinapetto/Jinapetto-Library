struct scc {
    vector<vector<int>> g, rg;
    vector<int> comp, ord, used;
    int n;
    int num;
    scc(int _n) : n(_n), g(_n), rg(_n), comp(_n, -1), ord(_n), used(_n) {}
    void add_e(int from, int to) {
        g[from].emplace_back(to);
        rg[to].emplace_back(from);
    }
    void dfs(int x) {
        if(used[x]) return;
        used[x] = true;
        for(int e : g[x])
            if(!used[e]) dfs(e);
        ord.emplace_back(x);
    }
    void rdfs(int x, int cnt) {
        if(comp[x] != -1) return;
        comp[x] = cnt;
        for(int e : rg[x])
            if(comp[e] == -1) rdfs(e, cnt);
    }
    vector<vector<int>> build() {
        // two-sat satisfied を複数回呼び出すときはコメントアウトしない
        // ord.assign(n, 0);
        // comp.assign(n, -1);
        // used.assign(n, false);
        num = 0;
        for(int i = 0; i < n; i++) dfs(i);
        reverse(ALL(ord));
        num = 0;
        for(int i : ord)
            if(comp[i] == -1) { rdfs(i, num), num++; }
        vector<vector<int>> ret(num);
        for(int i = 0; i < n; i++) ret[comp[i]].emplace_back(i);
        return ret;
    }
};