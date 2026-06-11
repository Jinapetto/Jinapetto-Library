#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define ALL(a) begin(a), end(a)

struct scc {
	vector<vector<int>> g,rg;
	vector<int> comp, ord, used;
	int n;
	int num;
	scc(int _n) : n(_n), g(_n), rg(_n), comp(_n, -1), ord(_n), used(_n) {}
	void add_e(int from,int to){
		g[from].emplace_back(to);
		rg[to].emplace_back(from);
	}
	void dfs(int x) {
		if(used[x]) return;
		used[x] = true;
		for(int e: g[x]) if(!used[e]) dfs(e);
		ord.emplace_back(x);
	}
	void rdfs(int x, int cnt) {
		if(comp[x] != -1) return;
		comp[x] = cnt;
		for(int e: rg[x]) if(comp[e] == -1) rdfs(e, cnt);
	}
	vector<vector<int>> build() {
		for(int i = 0;i < n;i++) dfs(i);
		reverse(ALL(ord));
		num = 0;
		for(int i : ord) if(comp[i] == -1) { rdfs(i, num), num++; }
		vector<vector<int>> ret(num);
		for(int i = 0;i < n;i++) ret[comp[i]].emplace_back(i);
		return ret;
	}
};

int main(){
	int n,m;
	cin >> n >> m;
	scc g(n);
	for(int i = 0;i < m;i++){
		int a,b;
		cin >> a >> b;
		g.add_e(a,b);
	}
	auto ans = g.build();
	cout << ans.size() << '\n';
	for(int i = 0;i < ans.size();i++){
		cout << ans[i].size() << ' ';
		for(int j = 0;j < ans[i].size();j++) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}