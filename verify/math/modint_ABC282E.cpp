//problem https://atcoder.jp/contests/abc282/tasks/abc282_e
#include <bits/stdc++.h>
using namespace std;
#include<atcoder/dsu>
using namespace atcoder;


#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int mod = 998244353;
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
	int n,m;
	cin >> n >> m;
	mod = m;
	vector<long long> a(n);
	rep(i,n) cin >> a[i];
	vector<tuple<long long,int,int>> v;
	for(int i = 0;i < n - 1;i++){
		for(int j = i + 1;j < n;j++){
			v.push_back({(mint(a[i]).pow(a[j]) + mint(a[j]).pow(a[i])).x,i,j});
		}
	}
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	dsu uf(n);
	long long ans = 0;
	rep(i,v.size()){
		auto [c,a,b] = v[i];
		if(uf.same(a,b)) continue;
		else {
			ans += c;
			uf.merge(a,b);
		}
	}
	cout << ans << endl;
	return 0;
}
