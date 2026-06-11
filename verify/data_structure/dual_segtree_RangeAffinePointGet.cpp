#include<bits/stdc++.h>
using namespace std;

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
            if(l & 1) lazy[l] = cp(lazy[l], f), ++l;
            if(r & 1) --r, lazy[r] = cp(lazy[r], f);
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
        for(int i = h; i > 0; i--) propagate(k >> i);
    }
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

using ll = long long;

using dat = pair<mint,mint>;

dat cp(dat a,dat b){
    return{a.first*b.first, a.second*b.first + b.second};
}

dat id(){return {mint(1),mint(0)};}

int main(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    dual_segtree<dat,cp,id> seg(n);
    for(;q--;){
        int t;
        cin >> t;
        if(t == 0){
            int l,r,b,c;
            cin >> l >> r >> b >> c;
            seg.apply(l,r,make_pair(mint(b),mint(c)));
        }else{
            int i;
            cin >> i;
            dat ret = seg.get(i);
            cout << (a[i]*ret.first + ret.second).x << '\n';
        }
    }
    return 0;
}
