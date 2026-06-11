class EulerTour {
public:
    vector<vector<pair<int, int>>> st;
    vector<int> lookup;

    void SparseTable(const vector<int>& v) {
        int b = 0;
        while((1 << b) <= v.size()) ++b;
        st.assign(b, vector<pair<int, int>>(1 << b));
        for(int i = 0; i < v.size(); i++) {
            st[0][i].first = v[i];
            st[0][i].second = i;
        }
        for(int i = 1; i < b; i++) {
            for(int j = 0; j + (1 << i) <= (1 << b); j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
        lookup.resize(v.size() + 1);
        for(int i = 2; i < lookup.size(); i++) { lookup[i] = lookup[i >> 1] + 1; }
    }

    inline pair<int, int> rmq(int l, int r) {
        int b = lookup[r - l];
        return min(st[b][l], st[b][r - (1 << b)]);
    }

    vector<int> idx, depth, in, out;
    vector<vector<int>> g;

    int n;
    EulerTour(int sz) : n(sz), in(sz, -1), out(sz, -1), g(sz) {
        idx.reserve(2 * n);
        depth.reserve(2 * n);
    }

    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void dfs(int cur, int pre, int dp) {
        in[cur] = idx.size();
        idx.push_back(cur);
        depth.push_back(dp);
        out[cur] = idx.size();
        for(int next : g[cur])
            if(next != pre) {
                dfs(next, cur, dp + 1);
                idx.push_back(cur);
                depth.push_back(dp);
                out[cur] = idx.size();
            }
    }

    void build(int root = 0) {
        dfs(root, -1, 0);
        SparseTable(depth);
    }

    int lca(int a, int b) {
        int l = min(in[a], in[b]);
        int r = max(out[a], out[b]);
        return idx[rmq(l, r).second];
    }
};
