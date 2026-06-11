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