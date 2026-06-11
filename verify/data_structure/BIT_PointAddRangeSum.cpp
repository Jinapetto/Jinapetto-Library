//problem https://judge.yosupo.jp/problem/point_add_range_sum
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
	vector<ll> a;
	BIT(ll n) : a(n + 1) {}
	void add(ll i, ll x) {
		i++;
		while(i < a.size()) a[i] += x, i += i & -i;
	}
	ll sum(ll r) {
		ll s = 0;
		while(r) s += a[r], r -= r & -r;
		return s;
	}
	ll sum(ll l, ll r) { return sum(r) - sum(l); }
	// minimize i s.t. sum(i) >= w
	int lower_bound(ll w) {
		if(w <= 0) return 0;
		int x = 0, N = a.size() + 1;
		for(int k = 1 << __lg(N); k; k >>= 1) {
			if(x + k <= N - 1 && a[x + k] < w) {
				w -= a[x + k];
				x += k;
			}
		}
		return x;
	}
};

int main(){
	int n,q;
	cin >> n >> q;
	BIT bit(n);
	for(int i = 0;i < n;i++){
		ll a;
		cin >> a;
		bit.add(i,a);
	}
	for(;q--;){
		int t;
		cin >> t;
		if(t == 0){
			int p,x;
			cin >> p >> x;
			bit.add(p,x);
		}else{
			int l,r;
			cin >> l >> r;
			cout << bit.sum(l,r) << '\n';
		}
	}
}
