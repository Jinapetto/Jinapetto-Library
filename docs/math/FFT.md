## 説明
FFTです。

modintに依存してます。
## コンストラクタ
mul(vector<mint> A,vector<mint> B) $C_k=\sum_{i+j=k}A_iB_i (mod m)$ を返します。
## 計算量
$O(N\log{N}+\log{mod})$
## 参考文献
https://x.com/noimi_kyopro/status/1834880895200719196
## verify
https://judge.yosupo.jp/submission/250785
## 備考
なんかバグってたから適当に直しました

998244353以外の原始根はよくわからんです
