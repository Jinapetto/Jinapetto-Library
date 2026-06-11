//problem:https://judge.yosupo.jp/problem/range_affine_range_sum

#include<bits/stdc++.h>
using namespace std;

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mp)(F, S), F (*cp)(F, F), F (*id)()>
struct lazy_segtree {
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    lazy_segtree(const vector<S>& v) : n(int(v.size())) {
		s = bit_ceil(uint64_t(n));
        log = countr_zero(uint64_t(s));
        d = vector<S>(2 * s, e());
        lz = vector<F>(s, id());
        for (int i = 0; i < n; i++) d[s + i] = v[i];
        for (int i = s - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        p += s;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        p += s;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if (l == r) return e();
        l += s;
        r += s;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        p += s;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mp(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        if (l == r) return;
        l += s;
        r += s;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <class G> int max_right(int l, G g) {
        assert(g(e()));
        if (l == n) return n;
        l += s;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < s) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - s;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template <class G> int min_left(int r, G g) {
        assert(g(e()));
        if (r == 0) return 0;
        r += s;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < s) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - s;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int n, s, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mp(f, d[k]);
        if (k < s) lz[k] = cp(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

const int MOD = 998244353;
using ll = long long;
using dat = pair<ll,ll>;

dat op(dat a,dat b){
	return {(a.first + b.first)%MOD,a.second + b.second};
}

dat e(){return {0LL,0LL};}

dat mp(dat f,dat x){
	return {(x.first*f.first + f.second*x.second)%MOD,x.second};
}

dat cp(dat f,dat g){
	return {(f.first*g.first)%MOD,(f.first*g.second + f.second)%MOD};
}

dat id(){return {1LL,0LL};}

int main(){
	int n,q;
	cin >> n >> q;
	vector<ll> a(n);
	for(int i = 0;i < n;i++) cin >> a[i];
	lazy_segtree<dat,op,e,dat,mp,cp,id> seg(n);
	for(int i = 0;i < n;i++) seg.set(i,{a[i],1});
	for(;q--;){
		int num;cin >> num;
		if(num == 0){
			int l,r;
			ll b,c;
			cin >> l >> r >> b >> c;
			seg.apply(l,r,{b,c});
		}else{
			int l,r;
			cin >> l >> r;
			cout << seg.prod(l,r).first << ' ';
		}
	}
}
