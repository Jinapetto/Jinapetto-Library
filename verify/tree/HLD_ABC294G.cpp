//problem https://atcoder.jp/contests/ABC294/tasks/abc294_g
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
//using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using Bint = mp::cpp_int;

const int INF = 1e9;
const int MOD = 998244353;
const long long LINF = 4e18;

using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using vvvvi = vector<vector<vector<vector<int>>>>;
using vvl = vector<vector<long long>>;
using vvvl = vector<vector<vector<long long>>>;
using vvvvl = vector<vector<vector<vector<long long>>>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvb = vector<vector<vector<bool>>>;
using vvvvb = vector<vector<vector<vector<bool>>>>;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define dump(x)  cout << #x << " = " << (x) << endl;
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define ALL(obj) (obj).begin(),(obj).end()

//https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp

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
  // par: 自分の親
  // sub: 部分木のサイズ（自分を含む）
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

	//子に対して値を貼る
	/*
		AB間の辺に重みを載せたいとき
		if(par[A] != B) swap(A, B);
		seg.set(vid[A], val);
		などとするとよい
	*/
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

ll op(ll a,ll b){
	return a + b;
}
ll e(){
	return 0;
}

segtree<ll,op,e> seg(2e5);

ll ans;
HLD hld(2e5);

void f(int l,int r){
	//dump(hld.inv[l])dump(hld.inv[r]);
	//dump(l)dump(r);
	ans += seg.prod(l,r);
	//dump(ans);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	
	vl w(n - 1);
	vi a(n - 1);
	vi b(n - 1);
	rep(i,n - 1){
		cin >> a[i] >> b[i] >> w[i];
		a[i]--;b[i]--;
		hld.add_edge(a[i],b[i]);
	}
	hld.build();
	rep(i,n - 1){
		int u = a[i];
		int v = b[i];
		if(hld.par[u] != v) swap(u,v);
		//dump(u);
		//dump(hld.vid[u]);
		//dump(w[i]);
		
		seg.set(hld.vid[u],w[i]);
	}
	int q;
	cin >> q;
	for(;q--;){
		int op;
		cin >> op;
		if(op == 1){
			int x;
			ll w;
			cin >> x >> w;
			x--;
			int u = a[x];
			int v = b[x];
			if(hld.par[u] != v) swap(u,v);
			seg.set(hld.vid[u],w);
		}else{
			int a,b;
			cin >> a >> b;
			a--;b--;
			ans = 0;
			hld.for_each_edge(a,b,f);
			cout << ans << "\n";
		}
	}
	return 0;
}
