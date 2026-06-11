// V dfs(vertex r, vertex v){
//    E prod = e();
//    for ( (v, c) in E, c in child(r,v) ){
//        prod = merge(prod, put_edge(dfs(r,c),idx(v,c)));
//    }
//    return put_vertex(prod, v);
// }

template<class E, class V, E (*merge)(E, E), E (*e)(), E (*put_edge)(V, int), V (*put_vertex)(E, int)>
struct RerootingDP {
    struct edge {
        int to, idx, xdi;
    };
    RerootingDP(int n_ = 0) : n(n_), inner_edge_id(0) {
        es.resize(2 * n - 2);
        start.resize(2 * n - 2);
        if(n == 1) es_build();
    }
    void add_edge(int u, int v, int idx, int xdi) {
        start[inner_edge_id] = u;
        es[inner_edge_id] = {v, idx, xdi};
        inner_edge_id++;
        start[inner_edge_id] = v;
        es[inner_edge_id] = {u, xdi, idx};
        inner_edge_id++;
        if(inner_edge_id == 2 * n - 2) { es_build(); }
    }
    vector<V> build(int root_ = 0) {
        root = root_;
        vector<V> subdp(n);
        subdp[0] = put_vertex(e(), 0);
        outs.resize(n);
        vector<int> geta(n + 1, 0);
        for(int i = 0; i < n; i++) geta[i + 1] = start[i + 1] - start[i] - 1;
        geta[root + 1]++;
        for(int i = 0; i < n; i++) geta[i + 1] += geta[i];
        dfs1(root, -1, subdp, geta);
        return subdp;
    }
    vector<V> reroot() {
        vector<E> reverse_edge(n);
        reverse_edge[root] = e();
        vector<V> answers(n);
        dfs2(root, reverse_edge, answers);
        return answers;
    }

private:
    int n, root, inner_edge_id;
    vector<E> outs;
    vector<edge> es;
    vector<int> start;
    int outs_start(int v) {
        int res = start[v] - v;
        if(root < v) res++;
        return res;
    }
    void es_build() {
        vector<edge> nes(2 * n - 2);
        vector<int> nstart(n + 2, 0);
        for(int i = 0; i < 2 * n - 2; i++) nstart[start[i] + 2]++;
        for(int i = 0; i < n; i++) nstart[i + 1] += nstart[i];
        for(int i = 0; i < 2 * n - 2; i++) nes[nstart[start[i] + 1]++] = es[i];
        swap(es, nes);
        swap(start, nstart);
    }
    void dfs1(int v, int f, vector<V>& subdp, vector<int>& geta) {
        E val = e();
        for(int i = start[v]; i < start[v + 1]; i++) {
            if(es[i].to == f) { swap(es[start[v + 1] - 1], es[i]); }
            if(es[i].to == f) continue;
            dfs1(es[i].to, v, subdp, geta);
            E nval = put_edge(subdp[es[i].to], es[i].idx);
            outs[geta[v]++] = nval;
            val = merge(val, nval);
        }
        subdp[v] = put_vertex(val, v);
    }
    void dfs2(int v, vector<E>& reverse_edge, vector<V>& answers) {
        int le = outs_start(v);
        int ri = outs_start(v + 1);
        int siz = ri - le;
        vector<E> rui(siz + 1);
        rui[siz] = e();
        for(int i = siz - 1; i >= 0; i--) { rui[i] = merge(outs[le + i], rui[i + 1]); }
        answers[v] = put_vertex(merge(rui[0], reverse_edge[v]), v);
        E lui = e();
        for(int i = 0; i < siz; i++) {
            V rdp = put_vertex(merge(merge(lui, rui[i + 1]), reverse_edge[v]), v);
            reverse_edge[es[start[v] + i].to] = put_edge(rdp, es[start[v] + i].xdi);
            lui = merge(lui, outs[le + i]);
            dfs2(es[start[v] + i].to, reverse_edge, answers);
        }
    }
};
