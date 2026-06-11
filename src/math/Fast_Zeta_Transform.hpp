// sを含むような上位集合 T についての f(T)の総和
// g(s) = \sum_{s \subseteq T} f(T)
// n = 1<<f.size()
template<typename T> vector<T> FZT(int n, vector<T> f) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) {
            if(!(j >> i & 1)) f[j] += f[j ^ (1 << i)];
        }
    }
    return f;
}

// Sに含まれる下位集合 tについての f(t)の総和
// g(S) = \sum_{t \subseteq S} f(t)
template<typename T> vector<T> FZT(int n, vector<T> f) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) {
            if(j >> i & 1) f[j] += f[j ^ (1 << i)];
        }
    }
    return f;
}