//problem https://judge.yosupo.jp/problem/vertex_add_path_sum
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define ALL(obj) (obj).begin(),(obj).end()

class HLD{
private:
  void dfs_sz(int v) {
    auto &es=G[v];
    if(~par[v]) es.erase(find(es.begin(),es.end(),par[v]));
    for(int &u:es){
      par[u]=v;
      dfs_sz(u);
      sub[v]+=sub[u];
      if(sub[u]>sub[es[0]]) swap(u,es[0]);
    }
  }

  void dfs_hld(int v,int &pos) {
    vid[v]=pos++;
    inv[vid[v]]=v;
    for(int u:G[v]){
      if(u==par[v]) continue;
      nxt[u]=(u==G[v][0]?nxt[v]:u);
      dfs_hld(u,pos);
    }
  }

public:
  vector< vector<int> > G;
  // vid: vertex -> idx
  // inv: idx -> vertex
  vector<int> vid,nxt,sub,par,inv;

  HLD(int n):G(n),vid(n,-1),nxt(n),sub(n,1),par(n,-1),inv(n){}

  void add_edge(int u,int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void build(int r=0) {
    int pos=0;
    dfs_sz(r);
    nxt[r]=r;
    dfs_hld(r,pos);
  }

  int lca(int u,int v){
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(nxt[u]==nxt[v]) return u;
      v=par[nxt[v]];
    }
  }

  template<typename F>
  void for_each(int u,int v,const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      f(max(vid[nxt[v]],vid[u]),vid[v]+1);
      if(nxt[u]!=nxt[v]) v=par[nxt[v]];
      else break;
    }
  }

  template<typename F>
  void for_each_edge(int u,int v,const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(nxt[u]!=nxt[v]){
        f(vid[nxt[v]],vid[v]+1);
        v=par[nxt[v]];
      }else{
        if(u!=v) f(vid[u]+1,vid[v]+1);
        break;
      }
    }
  }
};


template<class S, S (*op)(S, S), S (*e)()> struct segtree {
	segtree() : segtree(0) {}
	segtree(int n) : segtree(vector<S>(n, e())) {}
	segtree(const vector<S>& v) : n(v.size()) {
		s = bit_ceil(unsigned(n));
		log = countr_zero(unsigned(s));
		d = vector<S>(2 * s, e());
		for(int i = 0;i < n;i++) d[s + i] = v[i];
        for(int i = s - 1;i >= 1;i--) update(i);
	}

	void set(int p, S x) {
        p += s;
        d[p] = x;
        for(int i = 1;i <= log;i++) update(p >> i);
    }

	S get(int p) {
        return d[p + s];
    }

	S prod(int l, int r) const {
		S sml = e(), smr = e();
		l += s, r += s;
		while(l < r) {
			if(l & 1) sml = op(sml, d[l++]);
			if(r & 1) smr = op(d[--r], smr);
			l >>= 1, r >>= 1;
		}
		return op(sml, smr);
	}

	S all_prod() const {return d[1];}

	template<typename F> int max_right(int l, F f) const {
		if(l == n) return n;
		l += s;
		S sm = e();
		do {
			while(~l & 1) l >>= 1;
			if(!f(op(sm, d[l]))) {
				while(l < s) {
					l <<= 1;
					if(f(op(sm, d[l]))) sm = op(sm, d[l++]);
				}
				return l - s;
			}
			sm = op(sm, d[l++]);
		} while((l & -l) != l);
		return n;
	}

	template<typename F> int min_left(int r, F f) const {
		if(!r) return 0;
		r += s;
		S sm = e();
		do {
			r--;
			while(r > 1 and r & 1) r >>= 1;
			if(!f(op(d[r], sm))) {
				while(r < s) {
					r = (2 * r + 1);
					if(f(op(d[r], sm))) sm = op(d[r--], sm);
				}
				return r + 1 - s;
			}
			sm = op(d[r], sm);
		} while((r & -r) != r);
		return 0;
	}
	private:
	int n, s, log;
	vector<S> d;
	void update(int k) { d[k] = op(d[k * 2], d[k * 2 + 1]);}
};

ll op(ll a,ll b){return a + b;}
ll e(){return 0;}

int main(){
	int n,q;
	cin >> n >> q;
	HLD tree(n);
	vector<ll> a(n);
	for(int i = 0;i < n;i++) cin >> a[i];
	for(int i = 0;i < n - 1;i++){
		int u,v;
		cin >> u >> v;
		tree.add_edge(u,v);
	}
	tree.build();
	vector<ll> v(n);
	for(int i = 0;i < n;i++) v[tree.vid[i]] = a[i];
	segtree<ll,op,e> seg(v);
	for(;q--;){
		int t;
		cin >> t;
		if(t == 0){
			int p;ll x;
			cin >> p >> x;
			seg.set(tree.vid[p],seg.get(tree.vid[p]) + x);
		}else{
			int u,v;
			cin >> u >> v;
			ll ans = 0;
			tree.for_each(u,v,[&](int l,int r){ans += seg.prod(l,r);});
			cout << ans << '\n';
		}
	}
}
