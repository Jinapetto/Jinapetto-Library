// problem: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
#include <bits/stdc++.h>
// #include <atcoder/modint>
// #include <atcoder/convolution>
using namespace std;
// using namespace atcoder;
using ll = long long;
#define ALL(a) begin(a), end(a)
// using mint = modint998244353;

constexpr int mod = 998244353;
struct mint {
    int x;
    mint(long long x_ = 0) : x(x_ % mod) {
        if(x < 0) x == mod;
    }
    mint operator-() {
        auto res = *this;
        res.x = (x ? mod - x : 0);
        return res;
    }
    mint& operator+=(mint r) {
        if((x += r.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(mint r) {
        if((x -= r.x) < 0) x += mod;
        return *this;
    }
    mint& operator*=(mint r) {
        x = 1LL * x * r.x % mod;
        return *this;
    }
    mint& operator/=(mint r) { return *this *= r.inv(); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    mint inv() const { return pow(mod - 2); }
    mint pow(long long b) const {
        mint a = *this, c = 1;
        while(b) {
            if(b & 1) c *= a;
            a *= a;
            b >>= 1;
        }
        return c;
    }
};

mint g = 3;  // 原始根
void fft(vector<mint>& a, bool inv = false) {
    int n = a.size(), s = __lg(n);
    static vector<mint> z, iz;
    while(z.size() <= s) {
        z.emplace_back(g.pow(mint(mod - 1).x / (1 << z.size())));
        iz.emplace_back(z.back().inv());
    }
    vector<mint> b(n);
    for(int i = 1; i < s + 1; i++) {
        int w = 1 << s - i;
        mint base = inv ? iz[i] : z[i], now = 1;
        for(int y = 0; y < n / 2; y += w) {
            for(int x = 0; x < w; x++) {
                auto l = a[y << 1 | x], r = now * a[y << 1 | x | w];
                b[y | x] = l + r, b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

vector<mint> mul(vector<mint> a, vector<mint> b) {
    int n = a.size(), m = b.size();
    if(!n or !m) return {};
    if(min(n, m) <= 30) {
        vector<mint> ans(n + m - 1);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
        return ans;
    }
    int N = n + m - 1;
    int z = bit_ceil(unsigned(N));
    a.resize(z), b.resize(z);
    fft(a), fft(b);
    for(int i = 0; i < z; i++) a[i] *= b[i];
    fft(a, true);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for(auto&& e : a) e *= iz;
    return a;
}

// Calculate [x^N](P(x) / Q(x))
// - Coplexity: O(LlgLlgN) ( L = size(P) + size(Q) )
// - Reference: `Bostan–Mori algorithm` <https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a>
mint coefficient_of_rational_function(ll N, vector<mint> P, vector<mint> Q) {
    assert(N >= 0);
    // while (Q.size() and Q.back() == 0) Q.pop_back();
    while (Q.size() and Q.back().x == 0) Q.pop_back();
    assert(Q.size());
    int h = 0;
    // while (Q[h] == 0) h++;
    while (Q[h].x == 0) h++;
    N += h;
    Q.erase(Q.begin(), Q.begin() + h);

    if (Q.size() == 1) return N < int(P.size()) ? P[N] / Q[0] : 0;

    while (N) {
        vector<mint> g = Q;
        for (int i = 1; i < g.size(); i += 2) { g[i] = -g[i]; }
        // auto conv_P_g = convolution(P, g);
        auto conv_P_g = mul(P, g);
        P.resize((conv_P_g.size() + 1 - (N & 1)) / 2);
        for (int i = 0; i < P.size(); i++) { P[i] = conv_P_g[i * 2 + (N & 1)]; }
        // auto conv_Q_g = convolution(Q, g);
        auto conv_Q_g = mul(Q, g);
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
    // auto P = convolution(a, Q);
    auto P = mul(a, Q);
    P.resize(d);
    return coefficient_of_rational_function(k, P, Q);
}

int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int d;
    ll k;
    cin >> d >> k;
    vector<mint> a(d);
    for(int i = 0; i < d; i++){
        int tmp;
        cin >> tmp;
        a[i] = tmp;
    }
    vector<mint> c(d);
    for(int i = 0; i < d; i++){
        int tmp;
        cin >> tmp;
        c[i] = tmp;
    }
    cout << find_kth_term(a, c, k).x << '\n';
    return 0;
}