int MOD = 998244353;
long long mx_n = 5e3 + 10, mx_c = 5e3 + 10;
vector<vector<ll>> com(mx_n, vector<ll>(mx_c));
void init_com() {
    com[0][0] = 1;
    for(int i = 1;i < mx_n;i++){
        com[i][0] = 1;
        for(int j = 1;j < mx_c;j++){
            com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % MOD;
        }
    }
}
