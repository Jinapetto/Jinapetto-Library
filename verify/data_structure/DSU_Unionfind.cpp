//problem https://judge.yosupo.jp/problem/unionfind
#include <bits/stdc++.h>
using namespace std;

struct dsu {
    dsu(int sz) : n(sz), par(n, -1) {}

    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-par[x] < -par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int leader(int a) {
        if (par[a] < 0) return a;
        return par[a] = leader(par[a]);
    }

    int size(int a) {
        return -par[leader(a)];
    }

    vector<vector<int>> groups() {
    	vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int n;
    vector<int> par;
};

int main(){
	int n,q;
	cin >> n >> q;
	dsu uf(n);
	for(;q--;){
		int t,a,b;
		cin >> t >> a >> b;
		if(t == 0) uf.merge(a,b);
		else{
			if(uf.same(a,b)) cout << 1 << '\n';
			else cout << 0 << '\n';
		}
	}
}
