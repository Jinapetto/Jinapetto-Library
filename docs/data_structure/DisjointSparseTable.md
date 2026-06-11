## 説明
モノイドが載るSparse Tableです。
## コンストラクタ
disjoint_sparse_table<S,op,e> (vector< S >) 構築ACLのsegtreeと同じです。

S prod(int l, int r) [l,r)の演算結果を返す。
## 計算量
構築 $O(N\log{N})$

クエリ $O(1)$
## 参考文献
https://noshi91.hatenablog.com/entry/2023/04/07/165310
## verify
https://judge.yosupo.jp/submission/248196
## 備考
