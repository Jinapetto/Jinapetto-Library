// problem : https://judge.yosupo.jp/problem/two_sat
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define ALL(a) begin(a), end(a)

struct scc {
    vector<vector<int>> g, rg;
    vector<int> comp, ord, used;
    int n;
    int num;
    scc(int _n) : n(_n), g(_n), rg(_n), comp(_n, -1), ord(_n), used(_n) {}
    void add_e(int from, int to) {
        g[from].emplace_back(to);
        rg[to].emplace_back(from);
    }
    void dfs(int x) {
        if(used[x]) return;
        used[x] = true;
        for(int e : g[x])
            if(!used[e]) dfs(e);
        ord.emplace_back(x);
    }
    void rdfs(int x, int cnt) {
        if(comp[x] != -1) return;
        comp[x] = cnt;
        for(int e : rg[x])
            if(comp[e] == -1) rdfs(e, cnt);
    }
    vector<vector<int>> build() {
        for(int i = 0; i < n; i++) dfs(i);
        reverse(ALL(ord));
        num = 0;
        for(int i : ord)
            if(comp[i] == -1) { rdfs(i, num), num++; }
        vector<vector<int>> ret(num);
        for(int i = 0; i < n; i++) ret[comp[i]].emplace_back(i);
        return ret;
    }
};

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

int main(){
    int n, m;
    string s;
    char c;
    cin >> c >> s;
    cin >> n >> m;
    two_sat ts(n);
    for(int i = 0;i < m;i++){
        int a, b, c;
        cin >> a >> b >> c;
        ts.add_clause(abs(a) - 1, (a > 0 ? true : false), abs(b) - 1, (b > 0 ? true : false));
    }
    if(ts.satisfiable()){
        cout << "s SATISFIABLE\nv ";
        vector<bool> ans = ts.answer();
        for(int i = 0;i < n;i++) cout << (ans[i] ? i + 1 : -i - 1) << ' ';
        cout << "0\n";
    }else{
        cout << "s UNSATISFIABLE\n";
    }
}