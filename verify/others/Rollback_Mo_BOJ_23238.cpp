//problem https://www.acmicpc.net/problem/23238
#include <bits/stdc++.h>
using namespace std;

template<typename T,void (*add_l)(int), void (*add_r)(int), T (*out)(int,int), void (*snapshot)(), void (*rollback)(), void (*reset)()>
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
			return (c == d) ? (R[a] < R[b]) : (c < d);
		});

		vector<T> ret(Q);
		reset();
		snapshot();
		for(int i = 0;i < Q;i++){
			int pos = idx[i];
			if(R[pos] - L[pos] < width){
				for(int j = L[pos];j < R[pos];j++) add_r(j);
				ret[pos] = out(L[pos],R[pos]);
				rollback();
				snapshot();
			}
		}
		int cur_r = 0,pre_block = -1;
		for(int i = 0;i < Q;i++){
			int pos = idx[i];
			if(R[pos] - L[pos] < width) continue;
			int block = L[pos]/width;
			if(pre_block != block){
				reset();
				pre_block = block;
				cur_r = (block + 1)*width;
			}
			while(cur_r < R[pos]) add_r(cur_r++);
			snapshot();
			for(int j = (block + 1)*width - 1;j >= L[pos];j--) add_l(j);
			ret[pos] = out(L[pos],cur_r);
			rollback();
		}
		return ret;
	}
};

vector<int> mp(1e5);
vector<int> a;
int mx = 0;
int pos = -1;
vector<int> cnt;
int roll_mx = 0;
int roll_pos = -1;

void add(int i){
	mp[a[i]]++;
	if(mx < mp[a[i]]){
		mx = mp[a[i]];
		pos = a[i];
	}else if(mx == mp[a[i]] && pos < a[i]){
		pos = a[i];
	}
	cnt.push_back(a[i]);
}

int out(int l,int r){return pos;}

void snapshot(){
	roll_mx = mx;
	roll_pos = pos;
	cnt.clear();
}

void rollback(){
	for(int i : cnt){
		mp[i]--;
	}
	pos = roll_pos;
	mx = roll_mx;
}

void reset(){
	mx = 0,pos = -1;
	roll_mx = 0;roll_pos = -1;
	for(int i = 0;i < 1e5;i++) mp[i] = 0;
	cnt.clear();
}

int main(){
	int n,q;
	cin >> n >> q;
	a.resize(n);
	Mo<int,add,add,out,snapshot,rollback,reset> mo(n,q);
	for(int i = 0;i < n;i++) cin >> a[i];
	vector<int> b = a;
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	for(int i = 0;i < n;i++) a[i] = lower_bound(b.begin(),b.end(),a[i]) - b.begin();
	for(;q--;){
		int l,r;
		cin >> l >> r;
		l--;
		mo.add_q(l,r);
	}
	vector<int> ans = mo.run();
	for(int i = 0;i < ans.size();i++){
		cout << b[ans[i]] << '\n';
	}
}
