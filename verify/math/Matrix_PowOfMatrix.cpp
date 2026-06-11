#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define ALL(a) begin(a), end(a)


template<typename T> struct M {
	vector<vector<T>> a;
	int n, m;
	M(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}
	M(int n = 0) : M<T>(n, n) {}
	vector<T>& operator[](int k) { return a[k]; }
	const vector<T>& operator[](int k) const { return a[k]; }
	static M I(int n) {
		M mat(n);
		for(int i = 0;i < n;i++) mat[i][i] = 1;
		return mat;
	}
	M& operator+=(const M& b) {
		for(int i = 0;i < n;i++)for(int j = 0;j < m;j++) (*this)[i][j] += b[i][j];
		return *this;
	}
	M& operator-=(const M& b) {
		for(int i = 0;i < n;i++)for(int j = 0;j < m;j++) (*this)[i][j] -= b[i][j];
		return *this;
	}
	M& operator*=(const M& b) {
		int l = b.m;
		vector c(n, vector<T>(l));
		for(int i = 0;i < n;i++)for(int j = 0;j < m;j++) for(int k = 0;k < l;k++) c[i][k] += (*this)[i][j] * b[j][k];
		a.swap(c);
		return *this;
	}
	M& operator^=(ll k) {
		M b = M::I(n);
		while(k) {
			if(k & 1) b *= *this;
			*this *= *this;
			k >>= 1;
		}
		a.swap(b.a);
		return *this;
	}
	M operator+(const M& b) const { return (M(*this) += b); }
	M operator-(const M& b) const { return (M(*this) -= b); }
	M operator*(const M& b) const { return (M(*this) *= b); }
	M operator^(const M& b) const { return (M(*this) ^= b); }
};

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
   friend mint operator+(mint a, mint b) { return a += b; }
   friend mint operator-(mint a, mint b) { return a -= b; }
   friend mint operator*(mint a, mint b) { return a *= b; }
   friend mint operator/(mint a, mint b) { return a /= b; }
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
	int n;
	cin >> n;
	ll k;
	cin >> k;
	M<mint> a(n,n);
	for(int i = 0;i < n;i++)for(int j = 0;j < n;j++){
		int tmp;
		cin >> tmp;
		a[i][j] = tmp;
	}
	a ^= k;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cout << a[i][j].x << ' ';
		}
		cout << '\n';
	}
}