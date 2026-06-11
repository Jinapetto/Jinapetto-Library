template <class S, S (*op)(S, S), S (*e)()>
struct per_segtree {
private:
    struct Node {
        S d;
        int l, r;
    };

    int n{};
    vector<Node> pool;
    vector<int> roots;

    int create_node(const S& d, int l, int r) {
        pool.push_back({d, l, r});
        return (int)pool.size() - 1;
    }

    int merge(int l, int r) {
        return create_node(op(pool[l].d, pool[r].d), l, r);
    }

    int build(int l, int r, const vector<S>& v) {
        if (l + 1 == r) return create_node(v[l], -1, -1);
        int lp = build(l, (l + r) / 2, v);
        int rp = build((l + r) / 2, r, v);
        return merge(lp, rp);
    }

    int set(int a, const S& x, int k, int l, int r) {
        if (r <= a || a + 1 <= l) {
            return k;
        } else if (a <= l && r <= a + 1) {
            return create_node(x, -1, -1);
        } else {
            return merge(set(a, x, pool[k].l, l, (l + r) >> 1),
                         set(a, x, pool[k].r, (l + r) >> 1, r));
        }
    }

    int apply(int a, const S& x, int k, int l, int r) {
        if (r <= a || a + 1 <= l) {
            return k;
        } else if (a <= l && r <= a + 1) {
            return create_node(op(pool[k].d, x), -1, -1);
        } else {
            return merge(apply(a, x, pool[k].l, l, (l + r) >> 1),
                         apply(a, x, pool[k].r, (l + r) >> 1, r));
        }
    }

    S prod(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) {
            return e();
        } else if (a <= l && r <= b) {
            return pool[k].d;
        } else {
            return op(prod(a, b, pool[k].l, l, (l + r) >> 1),
                      prod(a, b, pool[k].r, (l + r) >> 1, r));
        }
    }

	template <class F>
    int max_right(int a, int k, int l, int r, S& sm, F f) const {
        if (r <= a) return r;
        if (a <= l && f(op(sm, pool[k].d))) {
            sm = op(sm, pool[k].d);
            return r;
        }
        if (l + 1 == r) return l;
        int mid = (l + r) / 2;
        int res = max_right(a, pool[k].l, l, mid, sm, f);
        if (res < mid) return res;
        return max_right(a, pool[k].r, mid, r, sm, f);
    }

    template <class F>
    int min_left(int b, int k, int l, int r, S& sm, F f) const {
        if (b <= l) return l;
        if (r <= b && f(op(pool[k].d, sm))) {
            sm = op(pool[k].d, sm);
            return l;
        }
        if (l + 1 == r) return r;
        int mid = (l + r) / 2;
        int res = min_left(b, pool[k].r, mid, r, sm, f);
        if (res > mid) return res;
        return min_left(b, pool[k].l, l, mid, sm, f);
    }

public:
    per_segtree() = default;

	explicit per_segtree(int n) : per_segtree(std::vector<S>(n, e())) {}

    explicit per_segtree(const vector<S>& v) : n((int)v.size()) {
        if (n > 0) {
            roots.push_back(build(0, n, v));
        }
    }

    void query_reserve(int q) {
        if (n == 0) return;
        int depth = 0;
        while ((1 << depth) < n) depth++;
        pool.reserve(2 * n + q * (depth + 1));
        roots.reserve(roots.size() + q);
    }

    int set(int version, int k, const S& x) {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= k && k < n);
        int new_root = set(k, x, roots[version], 0, n);
        roots.push_back(new_root);
        return (int)roots.size() - 1;
    }

    int apply(int version, int k, const S& x) {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= k && k < n);
        int new_root = apply(k, x, roots[version], 0, n);
        roots.push_back(new_root);
        return (int)roots.size() - 1;
    }

    S get(int version, int k) const {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= k && k < n);
        int t = roots[version];
        int l = 0, r = n;
        while (l + 1 < r) {
            int p = (l + r) / 2;
            if (k < p) {
                t = pool[t].l;
                r = p;
            } else {
                t = pool[t].r;
                l = p;
            }
        }
        return pool[t].d;
    }

    S prod(int version, int a, int b) const {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= a && a <= b && b <= n);
        return prod(a, b, roots[version], 0, n);
    }

    S all_prod(int version) const {
        assert(0 <= version && version < (int)roots.size());
        return pool[roots[version]].d;
    }

	template <class F>
    int max_right(int version, int l, F f) const {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= l && l <= n);
        assert(f(e()));
        if (l == n) return n;
        S sm = e();
        return max_right(l, roots[version], 0, n, sm, f);
    }

    template <class F>
    int min_left(int version, int r, F f) const {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= r && r <= n);
        assert(f(e()));
        if (r == 0) return 0;
        S sm = e();
        return min_left(r, roots[version], 0, n, sm, f);
    }
};