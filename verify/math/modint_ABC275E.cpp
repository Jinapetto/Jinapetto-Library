//problem https://atcoder.jp/contests/abc275/tasks/abc275_e
#include<bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
struct mint {
	int x;
	mint(long long x_ = 0) : x(x_ % mod) {
		if(x < 0) x == mod;
	}
	mint operator-() {
		auto res = *this;
		res.x = (x ? mod - x : 0);
		return res;
	}
	mint& operator+=(mint r) {
		if((x += r.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(mint r) {
		if((x -= r.x) < 0) x += mod;
		return *this;
	}
	mint& operator*=(mint r) {
		x = 1LL * x * r.x % mod;
		return *this;
	}
	mint& operator/=(mint r) { return *this *= r.inv(); }
	friend mint operator+(mint a, mint b) { return a += b;}
	friend mint operator-(mint a, mint b) { return a -= b;}
	friend mint operator*(mint a, mint b) { return a *= b;}
	friend mint operator/(mint a, mint b) { return a /= b;}
	mint inv() const { return pow(mod - 2); }
	mint pow(long long b) const {
		mint a = *this, c = 1;
		while(b) {
			if(b & 1) c *= a;
			a *= a;
			b >>= 1;
		}
	return c;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m,k;
	cin >> n >> m >> k;
	vector<mint> dp(n + 15);
	dp[0] = 1;
	for(int i = 0;i < k;i++){
		vector<mint> ndp(n + 15);
		for(int j = 0;j <= n + 13;j++){
			for(int k = 1;k <= m;k++){
				if(j < n){
					if(j + k < n + 15 && j + k != n) ndp[j + k] += dp[j]/m;
				}else if(j > n){
					if(j - k >= 0 && j - k != n) ndp[j - k] += dp[j]/m;
				}
			}
		}
		swap(dp,ndp);
	}
	mint ans = 1;
	for(int i = 0;i < n + 15;i++){
		ans -= dp[i];
	}
	cout << ans.x << endl;
	return 0;
}
