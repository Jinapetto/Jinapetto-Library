// problem : https://atcoder.jp/contests/abc428/tasks/abc428_f
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

const int INF = 1e9;
const int MOD = 998244353;
const long long LINF = 4e18;

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

template<typename F, F (*cp)(F, F), F (*id)()> struct dual_segtree {
    dual_segtree() : dual_segtree(0) {}
    dual_segtree(int n) : dual_segtree(vector<F>(n, id())) {}
    dual_segtree(const vector<F>& v) : n(int(v.size())) {
        sz = 1;
        h = 0;
        while(sz < n) sz <<= 1, h++;
        lazy.assign(2 * sz, id());
        for(int i = 0;i < n;i++) lazy[i + sz] = v[i];
    }

    F get(int k) {
        thrust(k += sz);
        return lazy[k];
    }

    F operator[](int k) { return get(k); }

    void apply(int a, int b, const F& f) {
        thrust(a += sz);
        thrust(b += sz - 1);
        for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) lazy[l] = cp(f, lazy[l]), ++l;
            if(r & 1) --r, lazy[r] = cp(f, lazy[r]);
        }
    }

private:
    int n, sz, h;
    vector<F> lazy;

    inline void propagate(int k) {
        lazy[2 * k + 0] = cp(lazy[k], lazy[2 * k + 0]);
        lazy[2 * k + 1] = cp(lazy[k], lazy[2 * k + 1]);
        lazy[k] = id();
    }

    inline void thrust(int k) {
        for(int i = h; i > 0; i--) propagate(k >> i);
    }
};

struct dat{
	bool is_l = true;
	ll val = -1;
};

dat cp(dat f, dat g){
	if(f.val == -1) return g;
	else return f;
}

dat id(){
	return dat();
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vl w(n);
	rep(i,n) cin >> w[i];
	dual_segtree<dat, cp, id> seg(vector<dat>(n, {true, 0}));
	int q;
	cin >> q;
	for(;q--;){
		int t;
		cin >> t;
		if(t == 1){
			ll i;
			cin >> i;
			i--;
			dat ret = seg.get(i);
			ll l;
			if(ret.is_l) l = ret.val;
			else l = ret.val - w[i];
			seg.apply(0, i + 1, {true, l});
		}else if(t == 2){
			ll i;
			cin >> i;
			i--;
			dat ret = seg.get(i);
			ll r;
			if(ret.is_l) r = ret.val + w[i];
			else r = ret.val;
			seg.apply(0, i + 1, {false, r});
		}else{
			ll x;
			cin >> x;
			ll ng = -1, ok = n;
			while(ok - ng > 1){
				ll mid = (ok + ng) / 2;
				dat ret = seg.get(mid);
				ll l, r;
				if(ret.is_l) l = ret.val, r = ret.val + w[mid];
				else l = ret.val - w[mid], r = ret.val;
				if(l <= x && x < r) ok = mid;
				else ng = mid;
			}
			cout << n - ok << '\n';
		}
		// rep(i,n) cout << seg.get(i).is_l << ' ' << seg.get(i).val << endl;
	}
	return 0;
}