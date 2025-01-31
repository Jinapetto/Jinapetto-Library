//problem : https://judge.yosupo.jp/problem/shortest_path
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

vector<ll> Dikstra(vector<vector<pair<int,ll>>> &g, int s){
    vector<ll> dist(g.size(),LINF);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>> > que;
    que.push({0,s});
    while(!que.empty()){
        auto [cost, cur] = que.top();
        que.pop();
        if(dist[cur] != LINF) continue;
        dist[cur] = cost;
        for(auto [next, w] : g[cur])if(dist[next] == LINF){
            que.push({cost + w, next});
        }
    }
    return dist;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int,ll>>> g(n);
    vector<vector<pair<int,ll>>> inv(n);
    rep(i,m){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        inv[b].push_back({a,c});
    }
    vector<ll> dist = Dikstra(g,s);
    if(dist[t] == LINF){
        cout << -1 << endl;
        return 0;
    }
    vector<int> ans;
    ans.reserve(n);
    int cur = t;
    ans.push_back(cur);
    vb vis(n,false);
    vis[t] = true;
    while(cur != s){
        for(auto [next,w] : inv[cur]){
            if(dist[next] + w == dist[cur] && !vis[next]){
                cur = next;
                break;
            }
        }
        vis[cur] = true;
        ans.push_back(cur);
    }
    reverse(ALL(ans));
    cout << dist[t] << ' ' << ans.size() - 1 << '\n';
    rep(i,ans.size() - 1) cout << ans[i] << ' ' << ans[i + 1] << '\n';
    return 0;
}
