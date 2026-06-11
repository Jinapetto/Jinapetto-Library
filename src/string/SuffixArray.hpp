// s[sa[0]:] < s[sa[1]:] < … < s[sa[n-1]:]
vector<int> SA(string s) {
    int n = s.size() + 1, lim = 256;
    vector<int> sa(n), x(s.begin(), s.end() + 1), y(n), ws(max(n, lim));
    iota(ALL(sa), 0);
    for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
        p = j;
        iota(ALL(y), n - j);
        for(int i = 0; i < n; i++)
            if(sa[i] >= j) y[p++] = sa[i] - j;
        fill(ALL(ws), 0);
        for(int i = 0; i < n; i++) ws[x[i]]++;
        for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
        for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
            x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
    }
    sa.erase(begin(sa));
    return sa;
}
