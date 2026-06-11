// problem : https://atcoder.jp/contests/abc425/tasks/abc425_e

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using Bint = mp::cpp_int;

const int INF = 2e9;
const long long LINF = 5e18;

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    ll m;
    cin >> t >> m;
    MOD = m;
    init_com();
    mint::set_mod(m);
    for(;t--;){
        int n;
        cin >> n;
        vi c(n);
        rep(i,n) cin >> c[i];
        mint ans = 1;
        int sum = 0;
        rep(i,n){
            sum += c[i];
            ans *= com[sum][c[i]];
        }
        cout << ans.val() << '\n';
    }
    return 0;
}
