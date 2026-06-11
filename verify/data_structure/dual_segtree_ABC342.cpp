// problem : https://atcoder.jp/contests/abc342/tasks/abc342_g
#include<bits/stdc++.h>
using namespace std;

template <typename F, F (*cp)(F, F), F (*id)()>
struct dual_segtree {
    dual_segtree() : dual_segtree(0) {}
    dual_segtree(int n) : dual_segtree(vector<F>(n,id())) {}
    dual_segtree(const vector<F>& v) : n(int(v.size())) {
        sz = 1;
        h = 0;
        while (sz < n) sz <<= 1, h++;
        lazy.assign(2 * sz, id());
    }

    F get(int k) {
        thrust(k += sz);
        return lazy[k];
    }

    F operator[](int k) { return get(k); }

    void apply(int a, int b, const F &f) {
        thrust(a += sz);
        thrust(b += sz - 1);
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lazy[l] = cp(lazy[l], f), ++l;
            if (r & 1) --r, lazy[r] = cp(lazy[r], f);
        }
    }

    private:
    int n, sz, h;
    vector<F> lazy;

    inline void propagate(int k) {
        lazy[2 * k + 0] = cp(lazy[2 * k + 0], lazy[k]);
        lazy[2 * k + 1] = cp(lazy[2 * k + 1], lazy[k]);
        lazy[k] = id();
    }

    inline void thrust(int k) {
        for (int i = h; i > 0; i--) propagate(k >> i);
    }
};

using ll = long long;

ll cp(ll f,ll g){return max(f,g);}
ll id(){return -1e18;}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> a(n);
    for(int i = 0;i < n;i++) cin >> a[i];
	int q;
	cin >> q;
	vector<int> t(q),l(q),r(q);
	vector<ll> x(q);
	for(int i = 0;i < q;i++){
		cin >> t[i];
		if(t[i] == 1) cin >> l[i] >> r[i] >> x[i],l[i]--;
		else cin >> x[i],x[i]--;
	}
	vector<bool> era1(q,false), era2(q,false);
	dual_segtree<ll,cp,id> seg;
	vector<int> idx;
	int sq = 1000;
	for(int i = 0;i < q;i++){
		if(i%sq == 0){
			idx.clear();
			for(int j = i;j < min(i + sq,q);j++){
				if(t[j] == 2){
					era1[x[j]] = true;
					idx.push_back(x[j]);
				}else if(t[j] == 1){
					idx.push_back(j);
					era2[j] = true;
				}
			}
            seg = dual_segtree<ll,cp,id>(n);
			for(int j = 0;j < i;j++){
				if(t[j] == 1 && (!era1[j] && !era2[j])) seg.apply(l[j],r[j],x[j]);
			}
		}
		
		if(t[i] == 1){
			era2[i] = false;
		}else if(t[i] == 2){
			era2[x[i]] = true;
		}else{
			ll ans = max(a[x[i]],seg.get(x[i]));
			for(int j : idx)if(!era2[j]){
				if(l[j] <= x[i] && x[i] < r[j]) ans = max(x[j],ans);
			}
			cout << ans << endl;
		}
	}
	return 0;
}
