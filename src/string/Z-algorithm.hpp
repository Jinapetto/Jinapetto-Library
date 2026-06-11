// z[i] = LCP(s[0]:, s[i]:)
vector<int> z_algorithm(const string& s) {
    int n = s.size(), l = -1, r = -1;
    vector<int> z(n, n);
    for(int i = 1; i < n; i++) {
        int& x = z[i] = i < r ? min<ll>(r - i, z[i - l]) : 0;
        while(i + x < n and s[i + x] == s[x]) x++;
        if(i + x > r) l = i, r = i + x;
    }
    return z;
}