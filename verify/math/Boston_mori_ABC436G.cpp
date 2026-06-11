// problem: https://atcoder.jp/contests/abc436/submissions/71821179
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

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

// Calculate [x^N](P(x) / Q(x))
// - Coplexity: O(LlgLlgN) ( L = size(P) + size(Q) )
// - Reference: `Bostan–Mori algorithm` <https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a>
mint coefficient_of_rational_function(ll N, vector<mint> P, vector<mint> Q) {
    assert(N >= 0);
    while (Q.size() and Q.back() == 0) Q.pop_back();
    // while (Q.size() and Q.back().x == 0) Q.pop_back();
    assert(Q.size());
    int h = 0;
    while (Q[h] == 0) h++;
    // while (Q[h].x == 0) h++;
    N += h;
    Q.erase(Q.begin(), Q.begin() + h);

    if (Q.size() == 1) return N < int(P.size()) ? P[N] / Q[0] : 0;

    while (N) {
        vector<mint> g = Q;
        for (int i = 1; i < g.size(); i += 2) { g[i] = -g[i]; }
        auto conv_P_g = convolution(P, g);
        // auto conv_P_g = mul(P, g);
        P.resize((conv_P_g.size() + 1 - (N & 1)) / 2);
        for (int i = 0; i < P.size(); i++) { P[i] = conv_P_g[i * 2 + (N & 1)]; }
        auto conv_Q_g = convolution(Q, g);
        // auto conv_Q_g = mul(Q, g);
        for (int i = 0; i < Q.size(); i++) { Q[i] = conv_Q_g[i * 2]; }
        N >>= 1;
    }
    return P[0] / Q[0];
}

// Find the n-th term of the sequence (0-ORIGIN)
// Complexity: O(K lg K \log N)
// a: 初期値 [a_0, a_1, ..., a_{d-1}]
// c: 漸化式の係数 [c_1, c_2, ..., c_d]
// 漸化式: a_i = \sum_{j=1}^d c_j * a_{i-j}
mint find_kth_term(vector<mint> a, vector<mint> c, ll k) {
    int d = c.size();
    assert(a.size() == d);
    vector<mint> Q(d + 1);
    Q[0] = 1;
    for (int i = 0; i < d; i++) Q[i + 1] = -c[i];
    auto P = convolution(a, Q);
    // auto P = mul(a, Q);
    P.resize(d);
    return coefficient_of_rational_function(k, P, Q);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;ll m;
    cin >> n >> m;
    vi a(n);
    rep(i,n) cin >> a[i];
    int sum = 0;
    rep(i,n) sum += a[i];
    vector<mint> dp(sum + 2);
    dp[0] = 1, dp[1] = -1;
    rep(i,n){
        vector<mint> ndp = dp;
        rep(j,sum + 2)if(dp[j] != 0){
            ndp[j + a[i]] -= dp[j];
        }
        swap(dp, ndp);
    }
    cout << coefficient_of_rational_function(m, vector<mint>({1}), dp).val() << endl;
    return 0;
}