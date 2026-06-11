// problem : https://atcoder.jp/contests/abc412/tasks/abc412_e
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

const int INF = 1e9;
const int MOD = 998244353;
const long long LINF = 4e18;

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

struct Eratosthenes_seg{
    vector<bool> isp_s;
    vector<bool> isp;
    int sqrt_r;
    Eratosthenes_seg(ll l, ll r){
        sqrt_r = ceil(sqrt(r));
        isp_s.assign(sqrt_r, true);
        isp_s[0] = isp_s[1] = false;
        for(int i = 2; i < sqrt_r; i++) {
            if(isp_s[i] == false) continue;
            for(int j = i * 2; j < sqrt_r; j += i) {
                isp_s[j] = false;
            }
        }
        
        isp.assign(r - l, true);
        for(int i = 0; i < min(2LL, r - l); i++) if(l + i < 2) isp[i] = false;

        for (ll i = 2; i < sqrt_r; i++) {
            if (!isp_s[i]) continue;
            ll k = max(i, (l + i - 1) / i);
            for (ll j = k * i; j < r; j += i) {
                isp[j - l] = false;
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll l, r;
    cin >> l >> r;
    r++;
    Eratosthenes_seg era(l, r);
    vector<bool> inc = era.isp;
    inc[0] = true;
    for(ll i = 2;i < era.sqrt_r;i++){
        if(!era.isp_s[i]) continue;
        for(__int128_t j = i * i;j < r;j *= i){
            if(l <= j && j < r) inc[j - l] = true;
        }
    }
    int ans = 0;
    rep(i, r - l) if(inc[i]) ans++;
    cout << ans << endl;
    return 0;
}