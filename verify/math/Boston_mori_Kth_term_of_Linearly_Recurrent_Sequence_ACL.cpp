// problem: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/convolution>
using namespace std;
using namespace atcoder;
using ll = long long;
#define ALL(a) begin(a), end(a)
using mint = modint998244353;

// Calculate [x^N](num(x) / den(x))
// - Coplexity: O(LlgLlgN) ( L = size(num) + size(den) )
// - Reference: `Bostan–Mori algorithm` <https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a>
mint coefficient_of_rational_function(ll N, vector<mint> num, vector<mint> den) {
    assert(N >= 0);
    while (den.size() and den.back() == 0) den.pop_back();
    assert(den.size());
    int h = 0;
    while (den[h] == 0) h++;
    N += h;
    den.erase(den.begin(), den.begin() + h);

    if (den.size() == 1) return N < int(num.size()) ? num[N] / den[0] : 0;

    while (N) {
        vector<mint> g = den;
        for (int i = 1; i < g.size(); i += 2) { g[i] = -g[i]; }
        auto conv_num_g = convolution(num, g);
        num.resize((conv_num_g.size() + 1 - (N & 1)) / 2);
        for (int i = 0; i < num.size(); i++) { num[i] = conv_num_g[i * 2 + (N & 1)]; }
        auto conv_den_g = convolution(den, g);
        for (int i = 0; i < den.size(); i++) { den[i] = conv_den_g[i * 2]; }
        N >>= 1;
    }
    return num[0] / den[0];
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
    cout << find_kth_term(a, c, k).val() << '\n';
    return 0;
}