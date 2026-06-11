template<typename T> struct M {
    vector<vector<T>> a;
    int n, m;
    M(int n, int m) : n(n), m(m), a(n, vector<T>(m)) {}
    M(int n = 0) : M<T>(n, n) {}
    vector<T>& operator[](int k) { return a[k]; }
    const vector<T>& operator[](int k) const { return a[k]; }
    static M I(int n) {
        M mat(n);
        for(int i = 0; i < n; i++) mat[i][i] = 1;
        return mat;
    }
    M& operator+=(const M& b) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] += b[i][j];
        return *this;
    }
    M& operator-=(const M& b) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) (*this)[i][j] -= b[i][j];
        return *this;
    }
    M& operator*=(const M& b) {
        int l = b.m;
        vector c(n, vector<T>(l));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < l; k++) c[i][k] += (*this)[i][j] * b[j][k];
        a.swap(c);
        return *this;
    }
    M& operator^=(ll k) {
        M b = M::I(n);
        while(k) {
            if(k & 1) b *= *this;
            *this *= *this;
            k >>= 1;
        }
        a.swap(b.a);
        return *this;
    }
    M operator+(const M& b) const { return (M(*this) += b); }
    M operator-(const M& b) const { return (M(*this) -= b); }
    M operator*(const M& b) const { return (M(*this) *= b); }
    M operator^(const M& b) const { return (M(*this) ^= b); }
};