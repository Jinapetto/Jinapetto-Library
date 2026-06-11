// add_clause -> satisfiable -> answer
struct two_sat {
    int n;
    scc g;
    vector<bool> ans;
    two_sat(int _n) : n(_n), g(2*n), ans(n) {}
    void add_clause(int i, bool f1, int j, bool f2) {
        g.add_e(2 * i + (f1 ? 0 : 1), 2 * j + (f2 ? 1 : 0));
        g.add_e(2 * j + (f2 ? 0 : 1), 2 * i + (f1 ? 1 : 0));
    }
    bool satisfiable() {
        vector<vector<int>> ret = g.build();
        vector<int> idx(2*n, -1);
        for(int i = 0;i < ret.size();i++){
            for(int j : ret[i]){
                idx[j] = i;
            }
        }
        for (int i = 0; i < n; i++) {
            if (idx[2 * i] == idx[2 * i + 1]) return false;
            ans[i] = idx[2 * i] < idx[2 * i + 1];
        }
        return true;
    }
    vector<bool> answer() { return ans; }
};