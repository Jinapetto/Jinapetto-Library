class Montgomery {
    ll mod;
    ll R;

public:
    Montgomery(ll n) : mod(n), R(n) {
        for(size_t i = 0; i < 5; ++i) { R *= 2 - mod * R; }
    }

    ll fma(ll a, ll b, ll c) const {
        const __uint128_t d = __uint128_t(a) * b;
        const ll e = c + mod + (d >> 64);
        const ll f = ll(d) * R;
        const ll g = (__uint128_t(f) * mod) >> 64;
        return e - g;
    }

    ll mul(ll a, ll b) const { return fma(a, b, 0); }
};

ll pollard_rho(ll n) {
    if(n % 2 == 0) { return 2; }
    const Montgomery m(n);

    constexpr ll C1 = 1;
    constexpr ll C2 = 2;
    constexpr ll M = 512;

    ll Z1 = 1;
    ll Z2 = 2;
retry:
    ll z1 = Z1;
    ll z2 = Z2;
    for(size_t k = M;; k *= 2) {
        const ll x1 = z1 + n;
        const ll x2 = z2 + n;
        for(size_t j = 0; j < k; j += M) {
            const ll y1 = z1;
            const ll y2 = z2;

            ll q1 = 1;
            ll q2 = 2;
            z1 = m.fma(z1, z1, C1);
            z2 = m.fma(z2, z2, C2);
            for(size_t i = 0; i < M; ++i) {
                const ll t1 = x1 - z1;
                const ll t2 = x2 - z2;
                z1 = m.fma(z1, z1, C1);
                z2 = m.fma(z2, z2, C2);
                q1 = m.mul(q1, t1);
                q2 = m.mul(q2, t2);
            }
            q1 = m.mul(q1, x1 - z1);
            q2 = m.mul(q2, x2 - z2);

            const ll q3 = m.mul(q1, q2);
            const ll g3 = gcd(n, q3);
            if(g3 == 1) { continue; }
            if(g3 != n) { return g3; }

            const ll g1 = gcd(n, q1);
            const ll g2 = gcd(n, q2);

            const ll C = g1 != 1 ? C1 : C2;
            const ll x = g1 != 1 ? x1 : x2;
            ll z = g1 != 1 ? y1 : y2;
            ll g = g1 != 1 ? g1 : g2;

            if(g == n) {
                do {
                    z = m.fma(z, z, C);
                    g = gcd(n, x - z);
                } while(g == 1);
            }
            if(g != n) { return g; }

            Z1 += 2;
            Z2 += 2;
            goto retry;
        }
    }
}

vector<pair<ll, int>> factorize(ll n) {
    if(n == 1) return {};
    map<ll, int> mp;
    queue<ll> divs;
    divs.push(n);
    while(!divs.empty()) {
        ll d = divs.front();
        divs.pop();
        if(is_prime(d)) {
            mp[d]++;
        } else {
            ll d1 = pollard_rho(d);
            ll d2 = d / d1;
            divs.push(d1);
            divs.push(d2);
        }
    }
    vector<pair<ll, int>> ret;
    for(auto [f, s] : mp) ret.push_back({f, s});
    return ret;
}

vector<ll> divisors(ll n) {
    vector<ll> ret({1});

    vector<pair<ll, int>> pr = factorize(n);

    for(pair<ll, int> p : pr) {
        int sz = ret.size();
        for(int i = 0; i < sz; i++) {
            ll v = 1;
            for(int j = 0; j < p.second; j++) {
                v *= p.first;
                ret.push_back(ret[i] * v);
            }
        }
    }
    return ret;
}
