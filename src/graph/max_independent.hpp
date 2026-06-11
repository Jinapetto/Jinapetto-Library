vector<int> max_independent(int n, vector<vector<bool>> g){
	int mid = n / 2;
	vector<bool> is_ind1(1<<mid, true);
	for(int i = 0;i < mid - 1;i++){
		for(int j = i + 1;j < mid;j++){
			if(g[i][j]) is_ind1[(1<<i) | (1<<j)] = false;
		}
	}
	for(int i = 0;i < (1<<mid);i++){
		if(!is_ind1[i]){
			for(int j = 0;j < mid;j++){
				if((i & (1<<j)) == 0){
					is_ind1[i | (1<<j)] = false;
				}
			}
		}
	}

	vector<bool> is_ind2(1<<(n - mid), true);
	for(int i = 0;i < (n - mid) - 1;i++){
		for(int j = i + 1;j < (n - mid);j++){
			if(g[mid + i][mid + j]) is_ind2[(1<<i) | (1<<j)] = false;
		}
	}
	for(int i = 0;i < (1<<(n - mid));i++){
		if(!is_ind2[i]){
			for(int j = 0;j < (n - mid);j++){
				if((i & (1<<j)) == 0){
					is_ind2[i | (1<<j)] = false;
				}
			}
		}
	}

	vector<int> not_connect(1<<mid);
	not_connect[0] = (1<<(n - mid)) - 1;
	for(int i = 0;i < mid;i++){
		for(int j = mid;j < n;j++){
			if(!g[i][j]) not_connect[1<<i] |= 1<<(j - mid);
		}
	}

	for(int i = 0;i < (1<<mid);i++){
		for(int j = 0;j < mid;j++){
			if((i & (1<<j)) == 0){
				not_connect[i | (1<<j)] = not_connect[i] & not_connect[1<<j];
			}
		}
	}

	vector<int> mx_sub_ind(1<<(n - mid));
	for(int i = 0;i < (1<<(n - mid));i++){
		if(is_ind2[i]) mx_sub_ind[i] = i;
		else mx_sub_ind[i] = 0;
	}

	for(int i = 0;i < (1<<(n - mid));i++){
		for(int j = 0;j < (n - mid);j++){
			if((i & (1<<j)) == 0 && __popcount(mx_sub_ind[i | (1<<j)]) < __popcount(mx_sub_ind[i])){
				mx_sub_ind[i | (1<<j)] = mx_sub_ind[i];
			}
		}
	}

	ll ans = 0;
	for(int i = 0;i < (1<<mid);i++){
		if(is_ind1[i]){
			ll cur = i | ((ll)mx_sub_ind[not_connect[i]] << mid);
			if(__popcount(ans) < __popcount(cur)){
				ans = cur;
			}
		}
	}

	vector<int> ret;
	rep(i,n)if(ans & (1LL<<i)) ret.push_back(i);
	return ret;
}