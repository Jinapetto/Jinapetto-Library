//problem https://onlinejudge.u-aizu.ac.jp/beta/room.html#ICPC_2019_Regional_1/problems/I
#include<bits/stdc++.h>
using namespace std;

struct LowLink {
  vector<vector<int>> &g;
  vector< int > used, ord, low;
  vector< int > arti;
  vector< pair< int, int > > bridge;
 
  LowLink(vector<vector<int>> &g) : g(g) {}
 
  int dfs(int idx, int k, int par) {
    used[idx] = true;
    ord[idx] = k++;
    low[idx] = ord[idx];
    bool is_arti = false;
    int cnt = 0;
    for(auto &to : g[idx]) {
      if(!used[to]) {
        ++cnt;
        k = dfs(to, k, idx);
        low[idx] = min(low[idx], low[to]);
        is_arti |= ~par && low[to] >= ord[idx];
        if(ord[idx] < low[to]) bridge.emplace_back(minmax(idx, (int) to));
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

class EulerTour{
	public:
  	vector< vector<pair<int,int>> > st;
  	vector< int > lookup;

  	void SparseTable(const vector< int > &v) {
	    int b = 0;
	    while((1 << b) <= v.size()) ++b;
	    st.assign(b, vector<pair<int,int>>(1 << b));
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
	    for(int i = 2; i < lookup.size(); i++) {
	      	lookup[i] = lookup[i >> 1] + 1;
	    }
  	}

  	inline pair<int,int> rmq(int l, int r) {
	    int b = lookup[r - l];
	    return min(st[b][l], st[b][r - (1 << b)]);
  	}

	vector<int> idx,depth,in,out;
	vector<vector<int>> g;

	int n;
	EulerTour(int sz):n(sz),in(sz,-1),out(sz,-1),g(sz){
		idx.reserve(2*n);
		depth.reserve(2*n);
	}

	void add_edge(int a,int b){
		g[a].push_back(b);
		g[b].push_back(a);
	}

	void dfs(int cur,int pre,int dp){
		in[cur] = idx.size();
		idx.push_back(cur);
		depth.push_back(dp);
		out[cur] = idx.size();
		for(int next : g[cur])if(next != pre){
			dfs(next,cur,dp + 1);
			idx.push_back(cur);
			depth.push_back(dp);
			out[cur] = idx.size();
		}
	}

	void build(int root = 0){
		dfs(root,-1,0);
		SparseTable(depth);
	}

	int lca(int a,int b){
		int l = min(in[a],in[b]);
		int r = max(out[a],out[b]);
		return idx[rmq(l,r).second];
	}
};

struct dsu {
    dsu(int sz) : n(sz), par(n, -1) {}

    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-par[x] < -par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int leader(int a) {
        if (par[a] < 0) return a;
        return par[a] = leader(par[a]);
    }

    int size(int a) {
        return -par[leader(a)];
    }

    vector<vector<int>> groups() {
    	vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int n;
    vector<int> par;
};

vector<bool> vis(2e5,false);
vector<pair<int,int>> ans(2e5,{-1,-1});
dsu uf(2e5);
vector<int> low(2e5);

void dfs(int cur,LowLink &LL,vector<vector<pair<int,int>>> &g,int cnt){
	low[cur] = cnt;
	vis[cur] = true;
	for(auto [next,idx] : g[cur])if(!vis[next]){
		if(LL.ord[cur] < LL.low[next] || LL.ord[next] < LL.low[cur]) continue;
		ans[idx] = {cur,next};
		uf.merge(cur,next);
		dfs(next,LL,g,cnt + 1);
	}
}

vector<vector<tuple<int,int,int,int>>> tree(2e5);
vector<int> imos1(2e5,0);
vector<int> imos2(2e5,0);

void dfs1(int cur,int pre){
	for(auto[next,idx,a,b] : tree[cur])if(next != pre){
		dfs1(next,cur);
		imos1[cur] += imos1[next];
		imos2[cur] += imos2[next];
		if(imos1[next] > 0) ans[idx] = {b,a};
		else ans[idx] = {a,b};
	}
	if((long long)imos1[cur]*imos2[cur] != 0){
		cout << "No" << endl;
		exit(0);
	}
}


int main(){
	int n,m;
	cin >> n >> m;
	vector<vector<int>> llg(n);
	vector<vector<pair<int,int>>> g(n);
	vector<int> a(m),b(m);
	for(int i = 0;i < m;i++){
		cin >> a[i] >> b[i];
		a[i]--,b[i]--;
		g[a[i]].push_back({b[i],i});
		g[b[i]].push_back({a[i],i});
		llg[a[i]].push_back(b[i]);
		llg[b[i]].push_back(a[i]);
	}
	LowLink LL(llg);
	LL.build();
	for(int i = 0;i < n;i++)if(!vis[i]){
		dfs(i,LL,g,0);
	}
	EulerTour lca(n);
	for(int i = 0;i < m;i++){
		if(uf.same(a[i],b[i])){
			if(ans[i].first == -1){
				if(low[a[i]] < low[b[i]]) ans[i] = {b[i],a[i]};
				else ans[i] = {a[i],b[i]};
			}
		}else{
			lca.add_edge(uf.leader(a[i]),uf.leader(b[i]));
			tree[uf.leader(a[i])].push_back({uf.leader(b[i]),i,a[i],b[i]});
			tree[uf.leader(b[i])].push_back({uf.leader(a[i]),i,b[i],a[i]});
		}
	}
	lca.build(uf.leader(0));
	int k;
	cin >> k;
	for(;k--;){
		int f,t;
		cin >> f >> t;
		f--,t--;
		if(uf.same(f,t)) continue;
		imos1[uf.leader(f)]++;
		imos2[uf.leader(t)]++;
		int tmp = lca.lca(uf.leader(f),uf.leader(t));
		imos1[tmp]--;
		imos2[tmp]--;
	}
	dfs1(uf.leader(0),-1);
	cout << "Yes\n";
	for(int i = 0;i < m;i++) cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
}
