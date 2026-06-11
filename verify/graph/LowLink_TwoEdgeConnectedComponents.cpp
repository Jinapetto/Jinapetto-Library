//problem https://judge.yosupo.jp/problem/two_edge_connected_components
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

vector<bool> vis(2e5,false);
vector<vector<int>> ans;
map<pair<int,int>,int> cnt;


void dfs(int cur,LowLink &LL,vector<vector<int>> &g){
	ans.back().push_back(cur);
	vis[cur] = true;
	for(int next : g[cur])if(!vis[next]){
		if(LL.ord[cur] < LL.low[next] || LL.ord[next] < LL.low[cur]){
			if(cnt[{min(cur,next),max(cur,next)}] == 1) continue;
		}
		dfs(next,LL,g);
	}
}

int main(){
	int n,m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for(int i = 0;i < m;i++){
		int a,b;
		cin >> a >> b;
		cnt[{min(a,b),max(a,b)}]++;
		if(cnt[{min(a,b),max(a,b)}] != 1) continue;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	LowLink LL(g);
	LL.build();
	for(int i = 0;i < n;i++)if(!vis[i]){
		ans.push_back({});
		dfs(i,LL,g);
	}
	cout << ans.size() << '\n';
	for(int i = 0;i < ans.size();i++){
		cout << ans[i].size() << ' ';
		for(int j = 0;j < ans[i].size();j++) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}
