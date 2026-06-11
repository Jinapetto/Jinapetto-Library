// problem : https://atcoder.jp/contests/abc359/tasks/abc359_g
#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
//using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

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

vi cnt(2e5 + 1);
vi cnt2(2e5 + 1);
vector<vector<int>> g(2e5);
vi a(2e5);
ll ans = 0;

void dfs1(int cur,int pre,vector<bool>& vis){
    cnt[a[cur]]++;
    for(int next : g[cur])if(next != pre && !vis[next]){
        dfs1(next,cur,vis);
    }
}

void dfs2(int cur,int pre,vector<bool>& vis){
    cnt2[a[cur]]++;
    for(int next : g[cur])if(next != pre && !vis[next]){
        dfs2(next,cur,vis);
    }
}

void dfs3(int cur,int pre,vector<bool>& vis,ll w_sum){
    for(int next : g[cur])if(next != pre && !vis[next]){
        dfs3(next,cur,vis,w_sum + 1);
    }
    ans += w_sum*(cnt[a[cur]] - cnt2[a[cur]]);
}

void dfs4(int cur,int pre,vector<bool>& vis){
    cnt2[a[cur]]--;
    for(int next : g[cur])if(next != pre && !vis[next]){
        dfs4(next,cur,vis);
    }
}

void dfs5(int cur,int pre,vector<bool>& vis){
    cnt[a[cur]]--;
    for(int next : g[cur])if(next != pre && !vis[next]){
        dfs5(next,cur,vis);
    }
}
struct CD {
   int v;
   vector<vector<int> > g;
   vector<bool> used;
   vector<int> sz, par;
   void calcsz(int u, int p) {
      sz[u] = 1;
      for(int v : g[u]) {
         if(!used[v] && v != p) {
            calcsz(v, u);
            sz[u] += sz[v];
         }
      }
   }
   void cdBuild(int u, int p) {
      calcsz(u, -1);
      int tot = sz[u];
      bool ok = false;
      int pp = -1;
      while(!ok) {
         ok = true;
         for(int v : g[u]) {
            if(!used[v] && v != pp && 2 * sz[v] > tot) {
               pp = u, u = v, ok = false;
               break;
            }
         }
      }
      par[u] = p;
      used[u] = true;
      //処理
        dfs1(u,-1,used);
        for(int next : g[u])if(!used[next]){
            dfs2(next,u,used);
            dfs3(next,u,used,1);
            dfs4(next,u,used);
        }
        dfs5(u,-1,used);


      for(int v : g[u]) {
         if(!used[v]) { cdBuild(v, u); }
      }
   }
   CD(int node_size) : v(node_size), g(v), used(v, false), sz(v, 0), par(v, -1) {}
   void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
   void build() { cdBuild(0, -1); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    CD tree(n);
    rep(i,n - 1){
        int u,v;
        ll w;
        cin >> u >> v;
        u--,v--;
        tree.add_edge(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rep(i,n) cin >> a[i];
    tree.build();
    cout << ans << endl;
    return 0;
}
