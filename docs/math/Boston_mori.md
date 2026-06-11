## 説明
線形漸化式に関する高速計算をするライブラリです。

## mint coefficient_of_rational_function(ll N, vector\<mint\> num, vector\<mint\> den)
$K$ 次多項式 $P(x), Q(x)$ に対して $[x^N]\frac{P(x)}{Q(x)}$ を計算します。

## mint find_kth_term(vector\<mint\> a, vector<\mint\> c, ll N)
$K$ 次多項式と先頭 $K$ 項 $[a_0,a_1,\dots,a_{K-1}]$ から第 $N$ 項を計算する。

## 計算量
coefficient_of_rational_function: $O(K\log{K}\log{N})$

find_kth_term: $O(K\log{K}\log{N})$

## 参考文献
https://hitonanode.github.io/cplib-cpp/formal_power_series/coeff_of_rational_function.hpp.html

## verify
https://judge.yosupo.jp/submission/338678

## 備考
