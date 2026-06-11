// problem: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d
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

template<typename W>
struct range_edge_graph {
    int n;
    struct edge { int to; W weight;};
    vector<vector<edge>> g;
    
    range_edge_graph(int n) : n(n) {
        g.resize(4*n);
        for (int i = 1; i < n; ++i) {
            int cl = i<<1|0, cr = i<<1|1;
            g[i].push_back({cl, 0});
            g[i].push_back({cr, 0});
            g[cl+2*n].push_back({i+2*n, 0});
            g[cr+2*n].push_back({i+2*n, 0});
        }
        for (int i = n; i < 2*n; ++i) g[i].push_back({i+2*n, 0});
    }

    // from [l1, r1) to [l2, r2)
    void add_edge(int l1, int r1, int l2, int r2, W w) {
        int idx = g.size();
        for (l1 += n, r1 += n; l1 < r1; l1 >>= 1, r1 >>= 1) {
            if (l1 & 1) g[l1+2*n].push_back({idx, 0}), l1++;
            if (r1 & 1) --r1, g[r1+2*n].push_back({idx, 0});
        }
        vector<edge> node;
        for (l2 += n, r2 += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) node.push_back({l2++, w});
            if (r2 & 1) node.push_back({--r2, w});
        }
        g.push_back(node);
    }

    vector<W> dijkstra(int s) {
        s += n;
        vector<W> dist(g.size(), numeric_limits<W>::max());
        dist[s] = 0;
        using P = pair<W, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(0, s);
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (edge& e : g[v]) {
                if (dist[e.to] > dist[v] + e.weight) {
                    dist[e.to] = dist[v] + e.weight;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        vector<W> res(dist.begin() + n, dist.begin() + 2*n);
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    range_edge_graph<ll> g(n);
    rep(i,m){
        int l, r;
        ll c;
        cin >> l >> r >> c;
        l--;
        g.add_edge(l, r, l, r, c);
    }
    ll ans = g.dijkstra(0)[n - 1];
    if(ans == numeric_limits<ll>::max()){
        cout << -1 << endl;
    }else{
        cout << g.dijkstra(0)[n - 1] << endl;
    }
    return 0;
}