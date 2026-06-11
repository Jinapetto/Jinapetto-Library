template<class S, S (*op)(S, S), S (*e)(), class F, S (*mp)(F, S), F (*cp)(F, F), F (*id)()> struct segtree_beats {
    segtree_beats() : segtree_beats(0) {}
    segtree_beats(int n) : segtree_beats(vector<S>(n, e())) {}
    segtree_beats(const vector<S>& v) : n(int(v.size())) {
        s = bit_ceil(uint64_t(n));
        log = countr_zero(uint64_t(s));
        d = vector<S>(2 * s, e());
        lz = vector<F>(s, id());
        for(int i = 0; i < n; i++) d[s + i] = v[i];
        for(int i = s - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        p += s;
        for(int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        p += s;
        for(int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if(l == r) return e();
        l += s;
        r += s;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push(r >> i);
        }
        S sml = e(), smr = e();
        while(l < r) {
            if(l & 1) sml = op(sml, d[l++]);
            if(r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        p += s;
        for(int i = log; i >= 1; i--) push(p >> i);
        d[p] = mp(f, d[p]);
        for(int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        if(l == r) return;
        l += s;
        r += s;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while(l < r) {
                if(l & 1) all_apply(l++, f);
                if(r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for(int i = 1; i <= log; i++) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template<class G> int max_right(int l, G g) {
        assert(g(e()));
        if(l == n) return n;
        l += s;
        for(int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while(l % 2 == 0) l >>= 1;
            if(!g(op(sm, d[l]))) {
                while(l < s) {
                    push(l);
                    l = (2 * l);
                    if(g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - s;
            }
            sm = op(sm, d[l]);
            l++;
        } while((l & -l) != l);
        return n;
    }

    template<class G> int min_left(int r, G g) {
        assert(g(e()));
        if(r == 0) return 0;
        r += s;
        for(int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while(r > 1 && (r % 2)) r >>= 1;
            if(!g(op(d[r], sm))) {
                while(r < s) {
                    push(r);
                    r = (2 * r + 1);
                    if(g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
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
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mp(f, d[k]);
        if(k < s) {
            lz[k] = cp(f, lz[k]);
            if(d[k].fail) push(k), update(k);
        }
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

// template <typename Num> inline Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept {
//     // a < a2, c < c2 のとき全引数を昇順ソートして二番目の値
//     return a == c ? min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : max(a, c);
// }
// template <typename Num> inline Num second_highest(Num a, Num a2, Num b, Num b2) noexcept {
//     // a > a2, b > b2 のとき全引数を降順ソートして二番目の値
//     return a == b ? max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : min(a, b);
// }

// using BNum = long long;
// constexpr BNum BINF = 1LL << 61;

// struct S {
//     BNum lo, hi, lo2, hi2, sum;  // 区間最小・最大値，区間最小・最大から二番目の値，区間総和
//     unsigned sz, nlo, nhi;       // 区間要素数，区間最小・最大値をとる要素の個数
//     bool fail;
//     S() : lo(BINF), hi(-BINF), lo2(BINF), hi2(-BINF), sum(0), sz(0), nlo(0), nhi(0), fail(0) {}
//     S(BNum x, unsigned sz_ = 1)
//         : lo(x), hi(x), lo2(BINF), hi2(-BINF), sum(x * sz_), sz(sz_), nlo(sz_), nhi(sz_), fail(0) {}
// };

// S e() { return S(); }

// S op(S l, S r) {
//     S ret;
//     ret.lo = min(l.lo, r.lo), ret.hi = max(l.hi, r.hi);
//     ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2);
//     ret.hi2 = second_highest(l.hi, l.hi2, r.hi, r.hi2);
//     ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;
//     ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
//     ret.nhi = l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);
//     return ret;
// }

// struct F {
//     BNum lb, ub, bias;
//     F(BNum chmax_ = -BINF, BNum chmin_ = BINF, BNum add = 0) : lb(chmax_), ub(chmin_), bias(add) {}
//     static F chmin(BNum x) noexcept { return F(-BINF, x, BNum(0)); }
//     static F chmax(BNum x) noexcept { return F(x, BINF, BNum(0)); }
//     static F add(BNum x) noexcept { return F(-BINF, BINF, x); };
// };

// F cp(F fnew, F fold) {
//     F ret;
//     ret.lb = max(min(fold.lb + fold.bias, fnew.ub), fnew.lb) - fold.bias;
//     ret.ub = min(max(fold.ub + fold.bias, fnew.lb), fnew.ub) - fold.bias;
//     ret.bias = fold.bias + fnew.bias;
//     return ret;
// }

// F id() { return F(); }

// S mp(F f, S x) {
//     if (x.sz == 0) return e();
//     else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub <= x.lo) {
//         return S(min(max(x.lo, f.lb), f.ub) + f.bias, x.sz);
//     } else if (x.lo2 == x.hi) {
//         x.lo = x.hi2 = max(x.lo, f.lb) + f.bias;
//         x.hi = x.lo2 = min(x.hi, f.ub) + f.bias;
//         x.sum = x.lo * x.nlo + x.hi * x.nhi;
//         return x;
//     } else if (f.lb < x.lo2 and f.ub > x.hi2) {
//         BNum nxt_lo = max(x.lo, f.lb), nxt_hi = min(x.hi, f.ub);
//         x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi - nxt_hi) * x.nhi + f.bias * x.sz;
//         x.lo = nxt_lo + f.bias, x.hi = nxt_hi + f.bias, x.lo2 += f.bias, x.hi2 += f.bias;
//         return x;
//     }
//     x.fail = 1;
//     return x;
// }
