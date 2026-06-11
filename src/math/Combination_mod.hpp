int MOD = 998244353;
long long maxnum = 1e7 + 10;
vector<long long> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac() {
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for(int i = 2; i < maxnum; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

long long combination_mod(long long n, long long r) {
    if(n < 0 or n - r < 0 or r < 0) return 0;
    return fac[n] * (finv[n - r] * finv[r] % MOD) % MOD;
}