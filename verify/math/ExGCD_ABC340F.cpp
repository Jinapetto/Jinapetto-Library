//problem https://atcoder.jp/contests/abc340/tasks/abc340_f
#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
//using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using Bint = mp::cpp_int;

const int INF = 2e9;
const int MOD = 998244353;
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

//"https://qiita.com/drken/items/b97ff231e43bce50199a"より引用
// 返り値: a と b の最大公約数
// ax + by = gcd(a, b) を満たす (x, y) が格納される
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

int main(){
	ll x,y;
	cin >> x >> y;
	if(gcd(x,y) == 1){
		ll a,b;
		extGCD(y,-x,a,b);
		cout << a*2 << ' ' << b*2 << endl;
	}else if(gcd(x,y) == 2){
		ll a,b;
		extGCD(y,-x,a,b);
		cout << a << ' ' << b << endl;
	}else{
		cout << -1 << endl;
	}
	return 0;
}
