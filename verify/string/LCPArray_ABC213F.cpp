//problem https://atcoder.jp/contests/ABC213/submissions/59927362
#include<bits/stdc++.h>
using namespace std;
#define ALL(a) begin(a), end(a)


vector<int> SA(string s) {
	int n = s.size() + 1, lim = 256;
	vector<int> sa(n), x(s.begin(),s.end() + 1), y(n), ws(max(n,lim));
	iota(ALL(sa), 0);
	for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p){
		p = j;
		iota(ALL(y), n - j);
		for(int i = 0;i < n;i++) if(sa[i] >= j) y[p++] = sa[i] - j;
		fill(ALL(ws), 0);
		for(int i = 0;i < n;i++) ws[x[i]]++;
		for(int i = 1;i < lim;i++) ws[i] += ws[i - 1];
		for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		for(int i = 1;i < n;i++) {
			int a = sa[i - 1], b = sa[i];
			x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ?p-1:p++;
		}
	}
	sa.erase(begin(sa));
	return sa;
}

//lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])
vector<int> LCP(string &s,vector<int> &sa){
	int n = sa.size();
	vector<int> rk(n),lcp(n - 1);
	for(int i = 0;i < n;i++) rk[sa[i]] = i;
	for(int i = 0, h = 0;i < n;i++){
		if(h) h--;
		if(rk[i] == n - 1) continue;
		int j = sa[rk[i] + 1];
		while(max(i,j) + h < n && s[i + h] == s[j + h]) h++;
		lcp[rk[i]] = h;
	}
	return lcp;
}
int main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<int> sa = SA(s);
	vector<int> lcp = LCP(s,sa);
	vector<long long> ans(n);
	for(int i = 0;i < n;i++) ans[i] = n - i;
	stack<pair<long long,long long>> st;
	long long sum = 0;
	for(int i = 0;i < n - 1;i++){
		long long cnt = 1;
		while(!st.empty() && st.top().first >= lcp[i]){
			sum -= st.top().first*st.top().second;
			cnt += st.top().second;
			st.pop();
		}
		sum += cnt*lcp[i];
		st.push({lcp[i],cnt});
		ans[sa[i + 1]] += sum;
	}
	sum = 0;
	stack<pair<long long,long long>> b;
	swap(st,b);
	for(int i = n - 2;i >= 0;i--){
		long long cnt = 1;
		while(!st.empty() && st.top().first >= lcp[i]){
			sum -= st.top().first*st.top().second;
			cnt += st.top().second;
			st.pop();
		}
		sum += cnt*lcp[i];
		st.push({lcp[i],cnt});
		ans[sa[i]] += sum;
	}
	for(int i = 0;i < n;i++) cout << ans[i] <<'\n';
	return 0;
}