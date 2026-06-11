//problem https://judge.yosupo.jp/problem/point_add_rectangle_sum
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define ALL(obj) (obj).begin(),(obj).end()

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
	segtree() : segtree(0) {}
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

template<typename T, T (*op)(T, T), T (*e)()> class RangeTree{
	private:
	int n, sz;
	vector<segtree<T, op, e>> seg;
	vector<vector<pair<ll,ll>>> yx;
	vector<pair<ll,ll>> sorted;
	void update_(int id, ll x, ll y, T val) {
		id += n - 1;
		int yid = lower_bound(ALL(yx[id]),make_pair(y,x)) - yx[id].begin();
		seg[id].set(yid, val);
		while(id > 0) {
			id = (id - 1) / 2;
			int yid = lower_bound(ALL(yx[id]),make_pair(y,x)) - yx[id].begin();
			seg[id].set(yid, val);
		}
	}
	T query(int lxid, int rxid, ll ly, ll ry, int k, int l,int r) {
		if(r <= lxid || rxid <= l) return e();
		if(lxid <= l && r <= rxid) {
			int lyid = lower_bound(ALL(yx[k]),make_pair(ly,(ll)-9e18)) - yx[k].begin();
			int ryid = lower_bound(ALL(yx[k]),make_pair(ry,(ll)-9e18)) - yx[k].begin();
			return (lyid >= ryid) ? e() : seg[k].prod(lyid,ryid);} else {
			return op(query(lxid, rxid, ly, ry, 2 * k + 1, l,(l+r) / 2),
			query(lxid, rxid, ly, ry, 2 * k + 2, (l+r)/ 2, r));
		}
	}
	public:
	// 座標, 点の値
	RangeTree(vector<pair<ll,ll>>& cand, vector<T>& val) : n(1), sz(cand.size()), sorted(sz) {
		while(n < sz) n *= 2;
		for(int i = 0;i < sz;i++) sorted[i] = {cand[i].first, i};
		sort(ALL(sorted), [&](pair<ll,ll>& a, pair<ll,ll>& b) {
			return (a.first == b.first) ? (cand[a.second].second<cand[b.second].second) : (a.first < b.first);
		});
		yx.resize(2 * n - 1), seg.resize(2 * n - 1);
		for(int i = 0;i < sz;i++) {
			yx[i + n - 1] = {{sorted[i].second, sorted[i].first}};
			vector<T> arg = {val[sorted[i].second]};
			seg[i + n - 1] = segtree<T, op, e>(arg);
			sorted[i].second = cand[sorted[i].second].second;
		}
		for(int i = n - 2;i >= 0;i--){
			yx[i].resize(yx[2 * i + 1].size() + yx[2 * i + 2].size());
			if(yx[i].empty()) continue;
			merge(ALL(yx[2 * i + 1]), ALL(yx[2 * i + 2]),yx[i].begin(), [&](pair<ll,ll>& a, pair<ll,ll>& b) {
				return (cand[a.first].second == cand[b.first].second) ? (a.second < b.second) : (cand[a.first].second < cand[b.first].second);
			});
			vector<T> arg((int)yx[i].size());
			for(int j = 0;j < yx[i].size();j++) arg[j] = val[yx[i][j].first];
			seg[i] = segtree<T, op, e>(arg);
		}
		for(int i = 0;i < 2 * n - 1;i++){
			for(auto& [a, b] : yx[i]) a = cand[a].second;
		}
	}
	void update(ll x, ll y, T val) {
		int id = lower_bound(ALL(sorted),make_pair(x,y)) - sorted.begin();
		return update_(id, x, y, val);
	}
	T query(ll lx, ll ly, ll rx, ll ry) {
		int lxid = lower_bound(ALL(sorted),make_pair(lx,(ll)-9e18)) - sorted.begin();
		int rxid = lower_bound(ALL(sorted),make_pair(rx,(ll)-9e18)) - sorted.begin();
		return (lxid >= rxid) ? e() : query(lxid, rxid, ly, ry, 0, 0, n);
	}
};

ll op(ll a,ll b){return a + b;}
ll e(){return 0LL;}

int main(){
	int n,q;
	cin >> n >> q;
	vector<pair<ll,ll>> cand;
	map<pair<ll,ll>,ll> mp;
	for(int i = 0;i < n;i++){
		ll x,y,w;
		cin >> x >> y >> w;
		mp[{x,y}] += w;
		cand.push_back({x,y});
	}
	vector<int> t(q);
	vector<ll> x(q),y(q),w(q);
	vector<ll> l(q),d(q),r(q),u(q);
	for(int i = 0;i < q;i++){
		cin >> t[i];
		if(t[i] == 0){
			cin >> x[i] >> y[i] >> w[i];
			cand.push_back({x[i],y[i]});
		}else{
			cin >> l[i] >> d[i] >> r[i] >> u[i];
		}
	}
	sort(ALL(cand));
	cand.erase(unique(ALL(cand)),cand.end());
	vector<ll> val(cand.size(),0);
	for(auto itr = mp.begin();itr != mp.end();itr++){
		int pos = lower_bound(ALL(cand),itr->first) - cand.begin();
		val[pos] = itr->second;
	}
	RangeTree<ll,op,e> seg(cand,val);
	for(int i = 0;i < q;i++){
		if(t[i] == 0){
			mp[{x[i],y[i]}] += w[i];
			seg.update(x[i],y[i],mp[{x[i],y[i]}]);
		}else{
			cout << seg.query(l[i],d[i],r[i],u[i]) << '\n';
		}
	}
	return 0;
}
