#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

//多倍長整数//
//#include <boost/multiprecision/cpp_int.hpp>
//namespace mp = boost::multiprecision;
//using bint = mp::cpp_int;

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

template< typename T, typename Compare = less< T >, typename RCompare = greater< T > >
struct PrioritySumStructure {

  size_t k;
  T sum;

  priority_queue< T, vector< T >, Compare > in, d_in;
  priority_queue< T, vector< T >, RCompare > out, d_out;

  PrioritySumStructure(int k) : k(k), sum(0) {}

  void modify() {
    while(in.size() - d_in.size() < k && !out.empty()) {
      auto p = out.top();
      out.pop();
      if(!d_out.empty() && p == d_out.top()) {
        d_out.pop();
      } else {
        sum += p;
        in.emplace(p);
      }
    }
    while(in.size() - d_in.size() > k) {
      auto p = in.top();
      in.pop();
      if(!d_in.empty() && p == d_in.top()) {
        d_in.pop();
      } else {
        sum -= p;
        out.emplace(p);
      }
    }
    while(!d_in.empty() && in.top() == d_in.top()) {
      in.pop();
      d_in.pop();
    }
  }

  T query() const {
    return sum;
  }

  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }

  void erase(T x) {
    assert(size());
    if(!in.empty() && in.top() == x) {
      sum -= x;
      in.pop();
    } else if(!in.empty() && RCompare()(in.top(), x)) {
      sum -= x;
      d_in.emplace(x);
    } else {
      d_out.emplace(x);
    }
    modify();
  }

  void set_k(size_t kk) {
    k = kk;
    modify();
  }

  size_t get_k() const {
    return k;
  }

  size_t size() const {
    return in.size() + out.size() - d_in.size() - d_out.size();
  }
};

template< typename T >
using MaximumSum = PrioritySumStructure< T, greater< T >, less< T > >;

template< typename T >
using MinimumSum = PrioritySumStructure< T, less< T >, greater< T > >;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vl a(n);
    vi b(n);
    rep(i,n) cin >> a[i] >> b[i];
    multiset<ll> st1, st2;
    ll sum2 = 0;
    int cnt2 = 0;
    ll base = 0;
    rep(i,n){
        if(b[i] == 1) st1.insert(a[i]);
        else st2.insert(a[i]), cnt2++, sum2 += a[i];
        base += a[i];
    }
    MaximumSum<ll> mx(cnt2);
    rep(i,n) mx.insert(a[i]);
    for(;q--;){
        int i, y;
        ll x;
        cin >> i >> x >> y;
        i--;
        base -= a[i];
        mx.erase(a[i]);
        if(b[i] == 2){
            cnt2--;
            sum2 -= a[i];
            st2.erase(st2.find(a[i]));
        }else{
            st1.erase(st1.find(a[i]));
        }
        a[i] = x, b[i] = y;
        base += a[i];
        mx.insert(a[i]);
        if(b[i] == 2){
            cnt2++;
            sum2 += a[i];
            st2.insert(a[i]);
        }else{
            st1.insert(a[i]);
        }
        mx.set_k(cnt2);
        ll topk = mx.query();
        if(cnt2 != 0 && topk == sum2){
            topk -= *st2.begin();
            if(!st1.empty()) topk += *st1.rbegin();
        }
        cout << base + topk << '\n';
    }
    return 0;
}
