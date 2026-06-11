//problem https://atcoder.jp/contests/abc458/tasks/abc458_f
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

const int INF = 1e9;
const int MOD = 998244353;
const long long LINF = 4e18;

using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using vvvvi = vector<vector<vector<vector<int>>>>;
using vvl = vector<vector<long long>>;
using vvvl = vector<vector<vector<long long>>>;
using vvvvl = vector<vector<vector<vector<long long>>>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvb = vector<vector<vector<bool>>>;
using vvvvb = vector<vector<vector<vector<bool>>>>;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define dump(x)  cout << #x << " = " << (x) << endl;
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define ALL(obj) (obj).begin(),(obj).end()

struct AhoCora{
    vector<vector<int>> g;
    vector<int> fail;
    vector<int> match;
    int char_sz, margin;

    AhoCora(int _char_sz, int _margin) : char_sz(_char_sz), margin(_margin){
        g.assign(1, vector<int>(char_sz, -1));
        match.assign(1, 0);
    }

    void add(string& s){
        _add(s, 0, 0);
    }

    void build(){
        int n = g.size();
        fail.assign(n, -1);
        fail[0] = 0;

        queue<int> que;

        for(int i = 0;i < char_sz;i++){
            if(g[0][i] == -1){
                g[0][i] = 0;
            }else{
                fail[g[0][i]] = 0;
                que.push(g[0][i]);
            }
        }

        while(!que.empty()){
            int cur = que.front();
            que.pop();

            match[cur] += match[fail[cur]];

            for(int i = 0;i < char_sz;i++){
                if(g[cur][i] == -1){
                    g[cur][i] = g[fail[cur]][i];
                }else{
                    fail[g[cur][i]] = g[fail[cur]][i];
                    que.push(g[cur][i]);
                }
            }
        }
    }

    private:

    void _add(string& s, int cur, int idx){
        if((int)s.size() == idx){
            match[cur]++;
            return;
        }
        if(g[cur][s[idx] - margin] == -1){
            g[cur][s[idx] - margin] = g.size();
            g.push_back(vector<int>(char_sz, -1));
            match.push_back(0);
        }
        _add(s, g[cur][s[idx] - margin], idx + 1);
    }
};

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    AhoCora ahocora(26, 'a');
    rep(i,k){
        string s;
        cin >> s;
        ahocora.add(s);
    }
    ahocora.build();

    int sz = ahocora.g.size();
    M<mint> a(sz, sz);
    rep(i,sz){
        rep(c,26){
            int ni = ahocora.g[i][c];
            if(ahocora.match[ni] == 0) a[ni][i] += 1;
        }
    }

    M<mint> b(sz, 1);
    b[0][0] = 1;

    a ^= n;
    b = a * b;
    mint ans = 0;
    rep(i,sz) ans += b[i][0];

    cout << ans.val() << endl;
    return 0;
}
