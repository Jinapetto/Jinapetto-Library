//problem https://judge.yosupo.jp/problem/tree_path_composite_sum
#include <bits/stdc++.h>
using namespace std;

// V dfs(vertex r, vertex v){
//    E prod = e();
//    for ( (v, c) in E, c in child(r,v) ){
//        prod = merge(prod, put_edge(dfs(r,c),idx(v,c)));
//    }
//    return put_vertex(prod, v);
// }

template <class E, class V, E (*merge)(E, E), E (*e)(), E (*put_edge)(V, int), V (*put_vertex)(E, int)>
struct RerootingDP {
    struct edge {
        int to, idx, xdi;
    };
    RerootingDP(int n_ = 0) : n(n_), inner_edge_id(0) {
        es.resize(2*n-2);
        start.resize(2*n-2);
        if (n == 1) es_build();
    }
    void add_edge(int u, int v, int idx, int xdi){
        start[inner_edge_id] = u;
        es[inner_edge_id] = {v,idx,xdi};
        inner_edge_id++;
        start[inner_edge_id] = v;
        es[inner_edge_id] = {u,xdi,idx};
        inner_edge_id++;
        if (inner_edge_id == 2*n-2){
            es_build();
        }
    }
    vector<V> build(int root_ = 0){
        root = root_;
        vector<V> subdp(n); subdp[0] = put_vertex(e(),0);
        outs.resize(n);
        vector<int> geta(n+1,0);
        for (int i = 0; i < n; i++) geta[i+1] = start[i+1] - start[i] - 1;
        geta[root+1]++;
        for (int i = 0; i < n; i++) geta[i+1] += geta[i];
        dfs1(root,-1,subdp,geta);
        return subdp;
    }
    vector<V> reroot(){
        vector<E> reverse_edge(n);
        reverse_edge[root] = e();
        vector<V> answers(n);
        dfs2(root,reverse_edge,answers);
        return answers;
    }
    private:
    int n, root, inner_edge_id;
    vector<E> outs;
    vector<edge> es;
    vector<int> start;
    int outs_start(int v){
        int res = start[v] - v;
        if (root < v) res++;
        return res;
    }
    void es_build(){
        vector<edge> nes(2*n-2);
        vector<int> nstart(n+2,0);
        for (int i = 0; i < 2*n-2; i++) nstart[start[i]+2]++;
        for (int i = 0; i < n; i++) nstart[i+1] += nstart[i];
        for (int i = 0; i < 2*n-2; i++) nes[nstart[start[i]+1]++] = es[i];
        swap(es,nes);
        swap(start,nstart);
    }
	void dfs1(int v,int f,vector<V> &subdp,vector<int> &geta){
        E val = e();
        for (int i = start[v]; i < start[v+1]; i++){
            if (es[i].to == f){
                swap(es[start[v+1]-1],es[i]);
            }
            if (es[i].to == f) continue;
            dfs1(es[i].to,v,subdp,geta);
            E nval = put_edge(subdp[es[i].to],es[i].idx);
            outs[geta[v]++] = nval;
            val = merge(val,nval);
        }
        subdp[v] = put_vertex(val, v);
    }
	void dfs2(int v,vector<E> &reverse_edge,vector<V> &answers){
        int le = outs_start(v);
        int ri = outs_start(v+1);
        int siz = ri - le;
        vector<E> rui(siz+1);
        rui[siz] = e();
        for (int i = siz-1; i >= 0; i--){
            rui[i] = merge(outs[le+i],rui[i+1]);
        }
        answers[v] = put_vertex(merge(rui[0],reverse_edge[v]),v);
        E lui = e();
        for (int i = 0; i < siz; i++){
            V rdp = put_vertex(merge(merge(lui,rui[i+1]),reverse_edge[v]),v);
            reverse_edge[es[start[v]+i].to] = put_edge(rdp,es[start[v]+i].xdi);
            lui = merge(lui,outs[le+i]);
            dfs2(es[start[v]+i].to,reverse_edge,answers);
        }
    }
};

constexpr int mod = 998244353;
struct mint {
	int x;
	mint(long long x_ = 0) : x(x_ % mod) {
		if(x < 0) x == mod;
	}
	mint operator-() {
		auto res = *this;
		res.x = (x ? mod - x : 0);
		return res;
	}
	mint& operator+=(mint r) {
		if((x += r.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(mint r) {
		if((x -= r.x) < 0) x += mod;
		return *this;
	}
	mint& operator*=(mint r) {
		x = 1LL * x * r.x % mod;
		return *this;
	}
	mint& operator/=(mint r) { return *this *= r.inv(); }
	friend mint operator+(mint a, mint b) { return a += b;}
	friend mint operator-(mint a, mint b) { return a -= b;}
	friend mint operator*(mint a, mint b) { return a *= b;}
	friend mint operator/(mint a, mint b) { return a /= b;}
	mint inv() const { return pow(mod - 2); }
	mint pow(long long b) const {
		mint a = *this, c = 1;
		while(b) {
			if(b & 1) c *= a;
			a *= a;
			b >>= 1;
		}
	return c;
	}
};

using dat = pair<mint,mint>;

vector<long long> a(2e5),b(2e5),c(2e5);

dat merge(dat a,dat b){
	return {a.first + b.first,a.second + b.second};
}

dat e(){
	return {0,0};
}

dat put_e(dat d,int i){
	return {d.first*b[i] + c[i]*d.second,d.second};
}

dat put_v(dat d,int i){
	return {d.first + a[i],d.second + 1};
}

int main(){
	int n;
	cin >> n;
	for(int i = 0;i < n;i++) cin >> a[i];
	RerootingDP<dat,dat,merge,e,put_e,put_v> dp(n);
	for(int i = 0;i < n - 1;i++){
		int u,v;
		cin >> u >> v;
		dp.add_edge(u,v,i,i);
		cin >> b[i] >> c[i];
	}
	dp.build();
	vector<dat> ans = dp.reroot();
	for(int i = 0;i < n;i++) cout << ans[i].first.x << ' ';
	cout << endl;
}
