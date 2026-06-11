#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
//using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

const int INF = 1e9;
const int MOD = 998244353;
const long long LINF = 4e18;

using ll = __int128_t;
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

// ax + by = gcd(a,b)
ll extGCD(ll a, ll b, ll& x, ll& y) {
   if(b == 0) {
      x = 1;
      y = 0;
      return a;
   }
   ll d = extGCD(b, a % b, y, x);
   y -= a / b * x;
   return d;
}
// x = x0 + t * b/gcd(a,b)
// y = y0 - t * a/gcd(a,b)

ll llceil(ll a,ll b){
	if(b < 0) a = -a,b = -b;
	return a > 0 ? (a - 1) / b + 1 : a / b;
}
 
ll llfloor(ll a,ll b){
	if(b < 0) a = -a,b = -b;
	return a >= 0 ? a / b : (a + 1) / b - 1;
}

pair<ll,ll> f(ll a,ll b,ll l,ll r){
	if(a > 0){
		return {llceil(l - b,a),llfloor(r - b,a)};
	}else{
		return {llceil(r - b,a),llfloor(l - b,a)};
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long _n,_a,_b,_c,_sum;
	cin >> _n >> _a >> _b >> _c >> _sum;

	ll n = _n,a = _a,b = _b,c = _c,sum = _sum;
	sum -= a + b + c;
	ll ans = 0;
	rep(i,n){
		ll cur = sum - a*i;
		if(cur < 0) break;
		// if(cur%gcd(b,c)) continue;
		ll x,y;
		ll g = extGCD(b,c,x,y);
		if(cur%g) continue;
		x *= cur/g;
		y *= cur/g;
		assert(x*b + y*c == cur);
		pair<ll,ll> seg1 = f(c/g,x,0,n - 1);
		pair<ll,ll> seg2 = f(-b/g,y,0,n - 1);
		ans += max((__int128_t)0,min(seg1.second,seg2.second) - max(seg1.first,seg2.first) + 1);
	}
	cout << (long long)ans << endl;
	return 0;
}