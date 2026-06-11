ll primitive_root(ll p) {
    if(p == 2) return 1LL;
    mt19937_64 mt((int)time(NULL));
    uniform_int_distribution<ll> rnd(1, p - 1);
    vector<pair<ll, int>> pps = factorize(p - 1);
    while(true) {
        ll r = rnd(mt);
        bool ok = true;
        for(auto [q, e] : pps) {
            if(mod_pow(r, (p - 1) / q, p) == 1) {
                ok = false;
                break;
            }
        }
        if(ok) return r;
    }
    return -1LL;
}