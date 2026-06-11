//problem https://judge.yosupo.jp/problem/point_add_range_sum

#include<bits/stdc++.h>
using namespace std;

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
	segtree(int n) : segtree(vector<S>(n, e())) {}
	segtree(const vector<S>& v) : n(v.size()) {
		s = bit_ceil(unsigned(n));
		log = countr_zero(unsigned(s));
		d = vector<S>(2 * s, e());
		for(int i = 0;i < n;i++) d[s + i] = v[i];
        for(int i = s - 1;i >= 1;i--) update(i);
	}

	void set(int p, S x) {
        p += s;
        d[p] = x;
        for(int i = 1;i <= log;i++) update(p >> i);
    }

	S get(int p) {
        return d[p + s];
    }

	S prod(int l, int r) const {
		S sml = e(), smr = e();
		l += s, r += s;
		while(l < r) {
			if(l & 1) sml = op(sml, d[l++]);
			if(r & 1) smr = op(d[--r], smr);
			l >>= 1, r >>= 1;
		}
		return op(sml, smr);
	}

	S all_prod() const {return d[1];}

	template<typename F> int max_right(int l, F f) const {
		if(l == n) return n;
		l += s;
		S sm = e();
		do {
			while(~l & 1) l >>= 1;
			if(!f(op(sm, d[l]))) {
				while(l < s) {
					l <<= 1;
					if(f(op(sm, d[l]))) sm = op(sm, d[l++]);
				}
				return l - s;
			}
			sm = op(sm, d[l++]);
		} while((l & -l) != l);
		return n;
	}

	template<typename F> int min_left(int r, F f) const {
		if(!r) return 0;
		r += s;
		S sm = e();
		do {
			r--;
			while(r > 1 and r & 1) r >>= 1;
			if(!f(op(d[r], sm))) {
				while(r < s) {
					r = (2 * r + 1);
					if(f(op(d[r], sm))) sm = op(d[r--], sm);
				}
				return r + 1 - s;
			}
			sm = op(d[r], sm);
		} while((r & -r) != r);
		return 0;
	}
	private:
	int n, s, log;
	vector<S> d;
	void update(int k) { d[k] = op(d[k * 2], d[k * 2 + 1]);}
};

using ll = long long;
ll op(ll a,ll b){return a + b;}
ll e(){return 0;}

int main(){
	int n,q;
	cin >> n >> q;
	vector<ll> a(n);
	for(int i = 0;i < n;i++) cin >> a[i];
	segtree<ll,op,e> seg(a);
	for(;q--;){
		int op;
		cin >> op;
		if(op == 1){
			int l,r;
			cin >> l >> r;
			cout << seg.prod(l,r) << '\n';
		}else{
			int p;
			cin >> p;
			ll x;
			cin >> x;
			seg.set(p,seg.get(p) + x);
		}
	}
	return 0;
}
