#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

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
#define ALL(obj) (obj).begin(),(obj).end()

struct Timer{
    chrono::steady_clock::time_point st;
    Timer(){
        st = chrono::steady_clock::now();
    }
    // 2sec -> 7e7 times
    inline double get(){
        return chrono::duration<double>(chrono::steady_clock::now() - st).count();
    }
} tim;

struct XorShift{
    uint64_t x = 2003082720030827ull;
    inline uint32_t operator()(){
        x^=x<<7;
        x^=x>>9;
        return (uint32_t)x; 
    }
    // [0, m)
    inline uint32_t i(uint32_t m){
        return m ? (uint32_t)((uint64_t)(*this)()*m >> 32) : (*this)();
    }
    // [0.0, 1.0)
    inline double d(){
        return (double)((*this)() & 0xFFFFFF) / 16777216.0;
    }
} rnd;

// 2sec -> 1e9 times
inline bool ac(double start_time, double cur_time, double end_time, double score_dist, double start_temp, double end_temp){
    double temp = start_temp + (end_temp - start_temp) * (cur_time - start_time) / (end_time - start_time);
    // double temp = start_temp * pow(end_temp / start_temp, (cur_time - start_time) / (end_time - start_time));
    if(score_dist >= 0.0) return true;
    if(score_dist <= -8.0 * temp) return false;
    return rnd.d() < exp(score_dist/temp);
}

// 2sec -> 7e8 times
inline double mn_ac(double start_time, double cur_time, double end_time, double start_temp, double end_temp){
    double temp = start_temp + (end_temp - start_temp) * (cur_time - start_time) / (end_time - start_time);
    // double temp = start_temp * pow(end_temp / start_temp, (cur_time - start_time) / (end_time - start_time));
    return log(rnd.d()) * temp;
}
