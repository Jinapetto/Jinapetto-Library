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