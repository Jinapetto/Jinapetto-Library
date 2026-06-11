// lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])
vector<int> LCP(string& s, vector<int>& sa) {
    int n = sa.size();
    vector<int> rk(n), lcp(n - 1);
    for(int i = 0; i < n; i++) rk[sa[i]] = i;
    for(int i = 0, h = 0; i < n; i++) {
        if(h) h--;
        if(rk[i] == n - 1) continue;
        int j = sa[rk[i] + 1];
        while(max(i, j) + h < n && s[i + h] == s[j + h]) h++;
        lcp[rk[i]] = h;
    }
    return lcp;
}