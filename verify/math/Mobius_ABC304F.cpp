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

class Eratosthenes{
	public:
	vector<bool> isprime;
	vector<int> minfactor;
	vector<int> mobius;

	Eratosthenes(int max_n){
		isprime.resize(max_n + 1,true);
		mobius.resize(max_n + 1,1);

		//エラトステネスの篩
		isprime[1] = false;
		
		for(int i = 2;i <= max_n;i++){
			if(isprime[i] == false) continue;
			mobius[i] = -1;

			for(int j = i*2;j <= max_n;j+=i){
				isprime[j] = false;
				if((j/i)%i == 0) mobius[j] = 0; //iで二回割り切れる
				else mobius[j] = -mobius[j]; //1->-1 or -1->1
			}
		}
	}
};

class Eratosthenes2{
	public:
	vector<bool> isprime;
	vector<int> minfactor;
	vector<int> mobius;

	Eratosthenes2(int max_n){
		isprime.resize(max_n + 1,true);
		minfactor.resize(max_n + 1,-1);
		mobius.resize(max_n + 1,1);

		//エラトステネスの篩
		isprime[1] = false;
		minfactor[1] = 1;
		
		for(int i = 2;i <= max_n;i++){
			if(isprime[i] == false) continue;
			mobius[i] = -1;
			minfactor[i] = i;

			for(int j = i*2;j <= max_n;j+=i){
				isprime[j] = false;
				if(minfactor[j] == -1) minfactor[j] = i;
				if((j/i)%i == 0) mobius[j] = 0; //iで二回割り切れる
				else mobius[j] = -mobius[j]; //1->-1 or -1->1
			}
		}
	}

	vector<pair<int,int>> factorize(int n){
		assert(1 < n && n < isprime.size());
		vector<pair<int,int>> ret;
		while(n > 1){
			//first
			int a = minfactor[n];
			//second
			int b = 0;
			while(minfactor[n] == a){
				b++;
				n /= a;
			}
			ret.push_back({a,b});
		}
		return ret;
	}

	vector<int> divisors(int n){
		vector<int> ret({1});

		vector<pair<int,int>> pr = factorize(n);

		for(pair<int,int> p : pr){
			int sz = ret.size();
			for(int i = 0;i < sz;i++){
				int v = 1;
				for(int j = 0;j < p.second;j++){
					v *= p.first;
					ret.push_back(ret[i]*v);
				}
			}
		}
		return ret;
	}
};

int main(){
	int n;
	string s;
	cin >> n >> s;
	Eratosthenes er(n);
	Eratosthenes2 er2(n);
	vi div = er2.divisors(n);
	vector<mint> F(n + 1);
	for(int v : div){
		//dump(v);
		vb free(v,true);
		rep(i,n) if(s[i] == '.') free[i%v] = false;
		int cnt = 0;
		rep(i,v) if(free[i]) cnt++;
		F[v] = mint(2).pow(cnt);
		//dump(F[v].val());
	}
	mint ans = 0;
	div.pop_back();
	for(int v : div){
		ans -= F[v]*er.mobius[n/v];
	}
	cout << ans.val() << endl;
	return 0;
}
