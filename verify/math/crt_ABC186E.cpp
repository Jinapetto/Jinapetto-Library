//problem https://atcoder.jp/contests/abc186/tasks/abc186_e
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll extGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

pair<ll,ll> crt(const vector<ll>& b, const vector<ll>& c) {
	int n = b.size();
	ll r = 0, m = 1;
	for(int i = 0;i < n;i++) {
		ll g, im, x;
		g = extGCD(m, c[i], im, x);
		if((b[i] - r) % g) return {0, -1};
		ll tmp = (b[i] - r) / g * im % (c[i] / g);
		r += m * tmp;
		m *= c[i] / g;
	}
	return {(r % m + m) % m, m};
}

int main(){
	int t;
	cin >> t;
	for(;t--;){
		ll n,s,k;
		cin >> n >> s >> k;

		pair<ll,ll> ans = crt({0, n - s},{k,n});
		if(ans.second == -1) cout << -1 << '\n';
		else cout << ans.first / k << '\n';
	}
}
