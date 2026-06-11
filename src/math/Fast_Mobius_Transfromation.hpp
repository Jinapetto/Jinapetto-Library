// s を含む上位集合 T についての包徐
// g(s) = \sum_{s \subseteq T} f(T) の逆変換
template<typename T> vector<T> FMT(int n, vector<T> g) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) {
            if(!(j >> i & 1)) g[j] -= g[j ^ (1 << i)];
        }
    }
    return g;
}

// S に含まれる下位集合 t についての包徐
// g(S) = \sum_{t \subseteq S} f(t)　の逆変換
template<typename T> vector<T> FMT(int n, vector<T> g) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) {
            if(j >> i & 1) g[j] -= g[j ^ (1 << i)];
        }
    }
    return g;
}