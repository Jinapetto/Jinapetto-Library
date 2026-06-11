## 説明
Baby-step Giant-step です。

${f(x)}^N = x$ となる関数 $f$ に対して\
${f(s)}^t = g$ となる最小の $t$ を求める
## ll bsgs\<T\>(T s, T g, ll n, ll m,const function<T(T)> &f,const function<T(T)> &fm)

f : T -> T f(x) 関数fをそのまま入れる\
fm : T -> T {f(x)}^M 関数fをM回したものを入れる

## 計算量
$O(M + N/M)$ \
M = $sqrt(N)$ で $O(√N)$

## 参考文献
https://atcoder.jp/contests/abc270/editorial/4965

## verify
https://atcoder.jp/contests/abc270/submissions/58147313
https://atcoder.jp/contests/abc186/submissions/68508018

## 備考
