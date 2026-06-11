ll mod_pow(ll x, ll y, ll mod) {
    ll ret = 1;
    ll acc = x;
    for(; y; y >>= 1) {
        if(y & 1) { ret = __uint128_t(ret) * acc % mod; }
        acc = __uint128_t(acc) * acc % mod;
    }
    return ret;
}

bool miller_rabin(ll n, const initializer_list<ll>& as) {
    return all_of(as.begin(), as.end(), [n](ll a) {
        if(n <= a) { return true; }

        int e = __builtin_ctzll(n - 1);
        ll z = mod_pow(a, (n - 1) >> e, n);
        if(z == 1 || z == n - 1) { return true; }

        while(--e) {
            z = __uint128_t(z) * z % n;
            if(z == 1) { return false; }
            if(z == n - 1) { return true; }
        }

        return false;
    });
}

bool is_prime(ll n) {
    if(n == 2) { return true; }
    if(n % 2 == 0) { return false; }
    if(n < 4759123141) { return miller_rabin(n, {2, 7, 61}); }
    return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}