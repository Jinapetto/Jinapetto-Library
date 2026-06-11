template<typename T>
ll bsgs(T s, T g, ll n, ll m,const function<T(T)> &f,const function<T(T)> &fm){
	map<T,ll> mp;
	for(int j = 1;j <= m;j++){
		g = f(g);
		mp[g] = j;
	}
	for(int i = 1;i <= (n + m - 1)/m;i++){
		s = fm(s);
		if(mp.count(s)) return m*i - mp[s];
	}
	return -1;
}
