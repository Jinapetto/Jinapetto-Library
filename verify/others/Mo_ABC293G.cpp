//problem https://atcoder.jp/contests/abc293/tasks/abc293_g
#include <bits/stdc++.h>
using namespace std;

template<typename T,void (*add_l)(int), void (*add_r)(int), void (*del_l)(int), void (*del_r)(int), T (*out)(int,int)>
class Mo{
	private:
		int width;
		vector<int> idx;
		vector<int> L,R;
		int N,Q;

	public:
	Mo(int n,int q){
		N = n;
		Q = q;
		width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
		L.reserve(q);
		R.reserve(q);
		idx.resize(q,0);
		iota(idx.begin(),idx.end(),0);
	}

	void add_q(int l,int r){
		assert(L.size() < Q);
		L.push_back(l);
		R.push_back(r);
	}

	vector<T> run(){
		sort(idx.begin(), idx.end(), [&](const int a, const int b){
            const int c = L[a] / width, d = L[b] / width;
            return (c == d) ? ((c & 1) ? (R[b] < R[a]) : (R[a] < R[b])) : (c < d);
        });

		vector<T> ret(Q);
		int cur_l = 0;int cur_r = 0;
		for(int i = 0;i < Q;i++){
			int pos = idx[i];
			while(L[pos] < cur_l) add_l(--cur_l);
			while(cur_r < R[pos]) add_r(cur_r++);

			while(cur_l < L[pos]) del_l(cur_l++);
			while(R[pos] < cur_r) del_r(--cur_r);
			ret[pos] = out(cur_l,cur_r);
		}
		return ret;
	}
};

long long comb(int n){
	return ((long long)n*(n - 1)*(n - 2))/6;
}

vector<int> a(2e5);
vector<int> cnt(2e5);
long long ans = 0;

void add_l(int l){
	if(cnt[a[l]] >= 3) ans -= comb(cnt[a[l]]);
	cnt[a[l]]++;
	if(cnt[a[l]] >= 3) ans += comb(cnt[a[l]]);
}

void add_r(int r){
	if(cnt[a[r]] >= 3) ans -= comb(cnt[a[r]]);
	cnt[a[r]]++;
	if(cnt[a[r]] >= 3) ans += comb(cnt[a[r]]);
}

void del_l(int l){
	if(cnt[a[l]] >= 3) ans -= comb(cnt[a[l]]);
	cnt[a[l]]--;
	if(cnt[a[l]] >= 3) ans += comb(cnt[a[l]]);
}

void del_r(int r){
	if(cnt[a[r]] >= 3) ans -= comb(cnt[a[r]]);
	cnt[a[r]]--;
	if(cnt[a[r]] >= 3) ans += comb(cnt[a[r]]);
}

long long out(int l,int r){
	return ans;
}

int main(){
	int n,q;
	cin >> n >> q;
	Mo<long long,add_l,add_r,del_l,del_r,out> mo(n,q);
	for(int i = 0;i < n;i++) cin >> a[i];
	for(int i = 0;i < n;i++) a[i]--;
	for(int i = 0;i < q;i++){
		int l,r;
		cin >> l >> r;
		l--;
		mo.add_q(l,r);
	}
	vector<long long> ans = mo.run();
	for(int i = 0;i < q;i++){
		cout << ans[i] << "\n";
	}
}
