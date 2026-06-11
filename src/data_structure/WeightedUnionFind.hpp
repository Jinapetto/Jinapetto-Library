class WeightedUnionFind {
private:
    int datasize;
    int inf_ = 1 << 30;
    vector<int> parent;
    vector<int> weight;
    bool check_ = true;

public:
    WeightedUnionFind(int size_) : datasize(size_), parent(size_, -1), weight(size_, 0) {}
    int find(int a) {
        if(parent[a] < 0) return a;
        int a2 = find(parent[a]);
        weight[a] += weight[parent[a]];
        return parent[a] = a2;
    }
    int get_weight(int a) {
        find(a);
        return weight[a];
    }
    bool merge(int a, int b, int d) {
        if(same(a, b) && diff(a, b) != d) check_ = false;
        d += get_weight(a);
        d -= get_weight(b);
        int a2 = find(a), b2 = find(b);
        if(a2 == b2) return false;
        if(parent[a2] > parent[b2]) {
            swap(a2, b2);
            d = -d;
        }
        parent[a2] += parent[b2];
        parent[b2] = a2;
        weight[b2] = d;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
    int diff(int a, int b) {
        if(!same(a, b)) return -inf_;
        return get_weight(b) - get_weight(a);
    }
    int size(int a) { return -parent[find(a)]; }
    vector<vector<int>> groups() {
        vector<int> leaders(datasize), groupsize(datasize);
        vector<vector<int>> res(datasize);
        for(int i = 0; i < datasize; i++) {
            leaders[i] = find(i);
            groupsize[leaders[i]]++;
        }
        for(int i = 0; i < datasize; i++) { res[i].reserve(groupsize[i]); }
        for(int i = 0; i < datasize; i++) { res[leaders[i]].push_back(i); }
        res.erase(remove_if(res.begin(), res.end(), [&](vector<int>& v) { return v.empty(); }), res.end());
        return res;
    }
    bool check() { return check_; }
};
