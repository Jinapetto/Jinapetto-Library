struct CD {
    int v;
    vector<vector<int> > g;
    vector<bool> used;
    vector<int> sz, par;
    void calcsz(int u, int p) {
        sz[u] = 1;
        for(int v : g[u]) {
            if(!used[v] && v != p) {
                calcsz(v, u);
                sz[u] += sz[v];
            }
        }
    }
    void cdBuild(int u, int p) {
        calcsz(u, -1);
        int tot = sz[u];
        bool ok = false;
        int pp = -1;
        while(!ok) {
            ok = true;
            for(int v : g[u]) {
                if(!used[v] && v != pp && 2 * sz[v] > tot) {
                    pp = u, u = v, ok = false;
                    break;
                }
            }
        }
        par[u] = p;
        used[u] = true;
        //処理
        // uが今回の重心である．used=trueとなっている頂点は重心として選ばれているため訪問しない処理を行う．
        //ここでused=trueとなっている頂点を訪問しないDFS,BFSなどをすることで全体の計算量がO(NlogN)となる．
        // parはその重心を取り除いた時の部分グラフの重心たちを結んだ木(?)を表している．
        for(int v : g[u]) {
            if(!used[v]) { cdBuild(v, u); }
        }
    }
    CD(int node_size) : v(node_size), g(v), used(v, false), sz(v, 0), par(v, -1) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    void build() { cdBuild(0, -1); }
};
