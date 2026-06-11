struct LowLink {
    vector<vector<int>>& g;
    vector<int> used, ord, low;
    vector<int> arti;
    vector<pair<int, int>> bridge;

    LowLink(vector<vector<int>>& g) : g(g) {}

    int dfs(int idx, int k, int par) {
        used[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_arti = false;
        int cnt = 0;
        for(auto& to : g[idx]) {
            if(!used[to]) {
                ++cnt;
                k = dfs(to, k, idx);
                low[idx] = min(low[idx], low[to]);
                is_arti |= ~par && low[to] >= ord[idx];
                if(ord[idx] < low[to]) bridge.emplace_back(minmax(idx, (int)to));
            } else if(to != par) {
                low[idx] = min(low[idx], ord[to]);
            }
        }
        is_arti |= par == -1 && cnt > 1;
        if(is_arti) arti.push_back(idx);
        return k;
    }

    virtual void build() {
        used.assign(g.size(), 0);
        ord.assign(g.size(), 0);
        low.assign(g.size(), 0);
        int k = 0;
        for(int i = 0; i < g.size(); i++) {
            if(!used[i]) k = dfs(i, k, -1);
        }
    }
};
// if bridge: parent->u, child->v, ord[u] < low[v]
