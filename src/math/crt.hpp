pair<ll, ll> crt(const vector<ll>& b, const vector<ll>& c) {
    int n = b.size();
    ll r = 0, m = 1;
    for(int i = 0; i < n; i++) {
        ll g, im, x;
        g = extGCD(m, c[i], im, x);
        if((b[i] - r) % g) return {0, -1};
        ll tmp = (b[i] - r) / g * im % (c[i] / g);
        r += m * tmp;
        m *= c[i] / g;
    }
    return {(r % m + m) % m, m};
}
