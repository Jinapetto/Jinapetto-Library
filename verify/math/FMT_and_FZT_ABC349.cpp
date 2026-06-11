//problem : https://atcoder.jp/contests/abc349/tasks/abc349_f
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

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

template<typename T>
vector<T> FZT(int n, vector<T> f)
{
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < (1 << n); ++j){
            if(j >> i & 1) f[j] += f[j ^ (1 << i)];
        }
    }
	return f;
}

template<typename T>
vector<T> FMT(int n, vector<T> g)
{
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < (1 << n); ++j){
            if(j >> i & 1) g[j] -= g[j ^ (1 << i)];
        }
    }
	return g;
}

int main(){
	int n;
	cin >> n;
	ll m;
	cin >> m;
	vector<pair<ll,int>> pr;
	ll mm = m;
	for(ll i = 2;i*i <= m;i++){
		while(mm%i == 0){
			mm /= i;
			if(!pr.empty() && pr.back().first == i) pr.back().second++;
			else pr.push_back({i,1});
		}
	}
	if(mm != 1) pr.push_back({mm,1});
	vl c(pr.size());
	rep(i,pr.size()){
		c[i] = 1;
		rep(j,pr[i].second) c[i] *= pr[i].first;
	}
	vi cnt(1<<c.size());
	rep(i,n){
		ll a;
		cin >> a;
		if(m % a != 0) continue;
		int bit = 0;
		rep(j,c.size()){
			if(a % c[j] == 0){
				a /= c[j];
				bit |= (1<<j);
			}
		}
		cnt[bit]++;
	}
	vector<int> z = FZT<int>(c.size(),cnt);
	vector<mint> b(1<<c.size());
	rep(i,1<<c.size()) b[i] = mint(2).pow(z[i]);
	vector<mint> ans = FMT<mint>(c.size(),b);
	if(m == 1){
		cout << (ans[(1<<c.size()) - 1] - 1).val() << endl;
	}else{
		cout << ans[(1<<c.size()) - 1].val() << endl;
	}
	return 0;
}
